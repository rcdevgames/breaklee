#include "PartyManager.h"

RTPartyManagerRef RTPartyManagerCreate(
    AllocatorRef Allocator,
    Index MaxPartyCount
) {
    RTPartyManagerRef PartyManager = AllocatorAllocate(Allocator, sizeof(struct _RTPartyManager));
    if (!PartyManager) Fatal("Memory allocation failed");

    PartyManager->PartyPool = MemoryPoolCreate(Allocator, sizeof(struct _RTParty), MaxPartyCount);
    PartyManager->PartyInvitationPool = MemoryPoolCreate(Allocator, sizeof(struct _RTPartyInvitation), MaxPartyCount);
    PartyManager->SoloPartyPool = MemoryPoolCreate(Allocator, sizeof(struct _RTParty), MaxPartyCount);
    PartyManager->CharacterToPartyEntity = IndexDictionaryCreate(Allocator, MaxPartyCount);
    PartyManager->CharacterToPartyInvite = IndexDictionaryCreate(Allocator, MaxPartyCount);

    Index NullIndex = 0;
    MemoryPoolReserve(PartyManager->PartyPool, NullIndex);
    MemoryPoolReserve(PartyManager->PartyInvitationPool, NullIndex);
    MemoryPoolReserve(PartyManager->SoloPartyPool, NullIndex);

    return PartyManager;
}

Void RTPartyManagerDestroy(
    RTPartyManagerRef PartyManager
) {
    MemoryPoolDestroy(PartyManager->PartyPool);
    MemoryPoolDestroy(PartyManager->PartyInvitationPool);
    MemoryPoolDestroy(PartyManager->SoloPartyPool);
    DictionaryDestroy(PartyManager->CharacterToPartyEntity);
    DictionaryDestroy(PartyManager->CharacterToPartyInvite);
    AllocatorDeallocate(PartyManager->Allocator, PartyManager);
}
// TODO: Solo dungeon party is not cleaned up always when the socket disconnects with a timeout (simulatable by halting on a breakpoint)
RTPartyRef RTPartyManagerCreateParty(
    RTPartyManagerRef PartyManager,
    Index CharacterIndex,
    RTEntityID CharacterID,
    Int32 PartyType
) {
    assert(!DictionaryLookup(PartyManager->CharacterToPartyEntity, &CharacterIndex));

    MemoryPoolRef PartyPool = PartyManager->PartyPool;
    if (PartyType == RUNTIME_PARTY_TYPE_SOLO_DUNGEON) {
        PartyPool = PartyManager->SoloPartyPool;
    }

    Index PartyPoolIndex = 0;
    RTPartyRef Party = (RTPartyRef)MemoryPoolReserveNext(PartyPool, &PartyPoolIndex);
    Party->ID.EntityIndex = (UInt16)PartyPoolIndex;
    Party->ID.WorldIndex = PartyType;
    Party->ID.EntityType = RUNTIME_ENTITY_TYPE_PARTY;
    Party->LeaderCharacterIndex = CharacterIndex;
    Party->PartyType = PartyType;
    RTPartyAddMember(Party, CharacterIndex, CharacterID);

    RTEntityID PartyID = { 0 };
    PartyID.EntityIndex = (UInt16)PartyPoolIndex;
    PartyID.WorldIndex = PartyType;
    PartyID.EntityType = RUNTIME_ENTITY_TYPE_PARTY;
    DictionaryInsert(PartyManager->CharacterToPartyEntity, &CharacterIndex, &PartyID, sizeof(struct _RTEntityID));

    return (RTPartyRef)MemoryPoolFetch(PartyPool, PartyPoolIndex);
}

RTPartyRef RTPartyManagerCreatePartyRemote(
    RTPartyManagerRef PartyManager,
    RTPartyRef RemoteParty
) {
    Index PartyPoolIndex = RemoteParty->ID.EntityIndex;
    if (!MemoryPoolIsReserved(PartyManager->PartyPool, PartyPoolIndex)) {
        RTPartyRef Party = (RTPartyRef)MemoryPoolReserve(PartyManager->PartyPool, PartyPoolIndex);
        memcpy(Party, RemoteParty, sizeof(struct _RTParty));

        for (Index MemberIndex = 0; MemberIndex < Party->MemberCount; MemberIndex += 1) {
            Index CharacterIndex = RemoteParty->Members[MemberIndex].Info.CharacterIndex;
            assert(!DictionaryLookup(PartyManager->CharacterToPartyEntity, &CharacterIndex));
            DictionaryInsert(PartyManager->CharacterToPartyEntity, &CharacterIndex, &Party->ID, sizeof(struct _RTEntityID));
        }

        return Party;
    }

    return (RTPartyRef)MemoryPoolFetch(PartyManager->PartyPool, PartyPoolIndex);
}

Void RTPartyManagerDestroyParty(
    RTPartyManagerRef PartyManager,
    RTPartyRef Party
) {
    // TODO: Cleanup also all invitations to this party!!!

    for (Index MemberIndex = 0; MemberIndex < Party->MemberCount; MemberIndex += 1) {
        Index CharacterIndex = Party->Members[MemberIndex].Info.CharacterIndex;
        DictionaryRemove(PartyManager->CharacterToPartyEntity, &CharacterIndex);
    }

    MemoryPoolRef PartyPool = PartyManager->PartyPool;
    if (Party->ID.WorldIndex == RUNTIME_PARTY_TYPE_SOLO_DUNGEON) {
        PartyPool = PartyManager->SoloPartyPool;
    }

    Index PartyPoolIndex = Party->ID.EntityIndex;
    MemoryPoolRelease(PartyPool, PartyPoolIndex);
}

Void RTPartyManagerDestroyPartyRemote(
    RTPartyManagerRef PartyManager,
    RTPartyRef RemoteParty
) {
    Index PartyPoolIndex = RemoteParty->ID.EntityIndex;
    if (MemoryPoolIsReserved(PartyManager->PartyPool, PartyPoolIndex)) {
        RTPartyManagerDestroyParty(PartyManager, RemoteParty);
    }
}

RTPartyRef RTPartyManagerGetPartyByCharacter(
    RTPartyManagerRef PartyManager,
    Index CharacterIndex
) {
    RTEntityID* PartyID = (RTEntityID*)DictionaryLookup(PartyManager->CharacterToPartyEntity, &CharacterIndex);
    if (!PartyID) return NULL;

    MemoryPoolRef PartyPool = PartyManager->PartyPool;
    if (PartyID->WorldIndex == RUNTIME_PARTY_TYPE_SOLO_DUNGEON) {
        PartyPool = PartyManager->SoloPartyPool;
    }

    Index PartyPoolIndex = PartyID->EntityIndex;
    return (RTPartyRef)MemoryPoolFetch(PartyPool, PartyPoolIndex);
}

RTPartyRef RTPartyManagerGetParty(
    RTPartyManagerRef PartyManager,
    RTEntityID PartyID
) {
    assert(PartyID.EntityType == RUNTIME_ENTITY_TYPE_PARTY);

    MemoryPoolRef PartyPool = PartyManager->PartyPool;
    if (PartyID.WorldIndex == RUNTIME_PARTY_TYPE_SOLO_DUNGEON) {
        PartyPool = PartyManager->SoloPartyPool;
    }

    Index PartyPoolIndex = PartyID.EntityIndex;
    if (!MemoryPoolIsReserved(PartyPool, PartyPoolIndex)) return NULL;

    return (RTPartyRef)MemoryPoolFetch(PartyPool, PartyPoolIndex);
}

Bool RTPartyManagerRemoveMember(
    RTPartyManagerRef PartyManager,
    Index CharacterIndex
) {
    RTEntityID* PartyID = (RTEntityID*)DictionaryLookup(PartyManager->CharacterToPartyEntity, &CharacterIndex);
    if (!PartyID) return false;

    MemoryPoolRef PartyPool = PartyManager->PartyPool;
    if (PartyID->WorldIndex == RUNTIME_PARTY_TYPE_SOLO_DUNGEON) {
        PartyPool = PartyManager->SoloPartyPool;
    }

    Index PartyPoolIndex = PartyID->EntityIndex;
    RTPartyRef Party = (RTPartyRef)MemoryPoolFetch(PartyPool, PartyPoolIndex);

    for (Int32 Index = 0; Index < Party->MemberCount; Index += 1) {
        if (Party->Members[Index].Info.CharacterIndex != CharacterIndex) continue;

        Int32 TailLength = Party->MemberCount - Index - 1;
        if (TailLength > 0) {
            memmove(&Party->Members[Index], &Party->Members[Index + 1], sizeof(struct _RTPartySlot) * TailLength);
        }

        Party->MemberCount -= 1;
        DictionaryRemove(PartyManager->CharacterToPartyEntity, &CharacterIndex);
        return true;
    }

    return false;
}
