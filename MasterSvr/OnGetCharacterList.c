#include "MasterDB.h"
#include "IPCProtocol.h"
#include "IPCProcedures.h"

IPC_PROCEDURE_BINDING(W2M, GET_CHARACTER_LIST) {
	memset(Account, 0, sizeof(MASTERDB_DATA_ACCOUNT));
	Account->AccountID = Packet->AccountID;
	if (!MasterDBGetOrCreateAccount(Context->Database, Account)) goto error;

	IPC_M2W_DATA_GET_CHARACTER_LIST* Response = IPCPacketBufferInit(Connection->PacketBuffer, M2W, GET_CHARACTER_LIST);
	Response->Header.Source = Server->IPCSocket->NodeID;
	Response->Header.Target = Packet->Header.Source;
	Response->Header.TargetConnectionID = Packet->Header.SourceConnectionID;
	
	StatementRef Statement = MasterDBSelectCharacterIndexByAccount(
		Context->Database,
		Packet->AccountID
	);
	if (!Statement) goto error;

	Int32 Index = 0;
	MASTERDB_DATA_CHARACTER_INDEX CharacterIndex = { 0 };
	while (MasterDBSelectCharacterIndexFetchNext(Context->Database, Statement, &CharacterIndex)) {
		assert(Index < MAX_CHARACTER_COUNT);

		// TODO: Add EquipmentAppearance

		Response->Characters[CharacterIndex.Index].ID = CharacterIndex.CharacterID;
		Response->Characters[CharacterIndex.Index].CreationDate = CharacterIndex.CreatedAt;
		Response->Characters[CharacterIndex.Index].Style = CharacterIndex.CharacterData.Style.RawValue;
		Response->Characters[CharacterIndex.Index].Level = CharacterIndex.CharacterData.Basic.Level;
		Response->Characters[CharacterIndex.Index].OverlordLevel = CharacterIndex.CharacterData.Overlord.Level;
		Response->Characters[CharacterIndex.Index].SkillRank = CharacterIndex.CharacterData.Skill.Rank;
		Response->Characters[CharacterIndex.Index].NationMask = CharacterIndex.CharacterData.Profile.Nation;
		CStringCopySafe(Response->Characters[CharacterIndex.Index].Name, MAX_CHARACTER_NAME_LENGTH + 1, CharacterIndex.Name);
		Response->Characters[CharacterIndex.Index].HonorPoint = CharacterIndex.CharacterData.Honor.Point;
		Response->Characters[CharacterIndex.Index].Alz = CharacterIndex.CharacterData.Currency[RUNTIME_CHARACTER_CURRENCY_ALZ];
		Response->Characters[CharacterIndex.Index].MapID = CharacterIndex.CharacterData.Position.WorldID;
		Response->Characters[CharacterIndex.Index].PositionX = CharacterIndex.CharacterData.Position.X;
		Response->Characters[CharacterIndex.Index].PositionY = CharacterIndex.CharacterData.Position.Y;
		Response->Characters[CharacterIndex.Index].EquipmentCount = CharacterIndex.EquipmentData.Count;
		memcpy(Response->Characters[CharacterIndex.Index].Equipment, CharacterIndex.EquipmentData.Slots, sizeof(struct _RTItemSlot) * CharacterIndex.EquipmentData.Count);

		Index += 1;
		memset(&CharacterIndex, 0, sizeof(MASTERDB_DATA_CHARACTER_INDEX));
	}

    IPCSocketUnicast(Socket, Response);
    return;

error:
	return;
}