#pragma once

#include "Base.h"
#include "Server.h"

EXTERN_C_BEGIN

Void BroadcastMessage(
    ServerContextRef Context,
    CString Message
);

Void BroadcastUserList(
    ServerRef Server,
    ServerContextRef Context
);

Void BroadcastToParty(
    ServerContextRef Context,
    RTEntityID PartyID,
    Void *Notification
);

Void BroadcastToWorld(
    ServerContextRef Context,
    RTWorldContextRef World,
    RTEntityID Entity,
    Int32 X,
    Int32 Y,
    Void *Packet
);

Void SendGiftBoxPricePoolList(
    ServerContextRef Context,
    ClientContextRef Client
);

Void SendPremiumServiceList(
    ServerContextRef Context,
    SocketRef Socket,
    SocketConnectionRef Connection
);

Void SendCharacterStatus(
    ServerContextRef Context,
    SocketRef Socket,
    SocketConnectionRef Connection,
    RTCharacterRef Character
);

Void SendPartyData(
    ServerContextRef Context,
    SocketRef Socket,
    RTPartyRef Party
);

EXTERN_C_END
