#include "Context.h"
#include "Server.h"
#include "MasterDB.h"
#include "IPCProcs.h"
#include "IPCSocket.h"

#define IPC_AUTH_PROCEDURE(__NAME__, __COMMAND__, __PROTOCOL__) \
Void SERVER_AUTH_ ## __NAME__(                                  \
    ServerRef Server,                                           \
    Void *ServerContext,                                        \
    SocketRef Socket,                                           \
    SocketConnectionRef Connection,                             \
    Void *ConnectionContext,                                    \
    Void *Packet                                                \
) {                                                             \
    __NAME__(                                                   \
        Server,                                                 \
        (ServerContextRef)ServerContext,                        \
        Socket,                                                 \
        Connection,                                             \
        (ClientContextRef)ConnectionContext,                    \
        (__PROTOCOL__*)Packet                                   \
    );                                                          \
}
#include "IPCProcDefinition.h"

#define IPC_WORLD_PROCEDURE(__NAME__, __COMMAND__, __PROTOCOL__) \
Void SERVER_WORLD_ ## __NAME__(                                  \
    ServerRef Server,                                            \
    Void *ServerContext,                                         \
    SocketRef Socket,                                            \
    SocketConnectionRef Connection,                              \
    Void *ConnectionContext,                                     \
    Void *Packet                                                 \
) {                                                              \
    __NAME__(                                                    \
        Server,                                                  \
        (ServerContextRef)ServerContext,                         \
        Socket,                                                  \
        Connection,                                              \
        (ClientContextRef)ConnectionContext,                     \
        (__PROTOCOL__*)Packet                                    \
    );                                                           \
}
#include "IPCProcDefinition.h"

Void ServerOnUpdate(
    ServerRef Server,
    Void *ServerContext
) {
    ServerContextRef Context = (ServerContextRef)ServerContext;
    Bool IsAuthSocketConnected = Context->AuthSocket->Flags & SOCKET_FLAGS_CONNECTED;
    if (Context->WorldListBroadcastTimestamp < Context->WorldListUpdateTimestamp && IsAuthSocketConnected) {
        Context->WorldListBroadcastTimestamp = ServerGetTimestamp(Server);
        Context->WorldListUpdateTimestamp = Context->WorldListBroadcastTimestamp;
        ServerBroadcastWorldList(Server, Context);
    }
}

Int32 main(Int32 argc, CString* argv) {
    DiagnosticCreateLogFile("MasterSvr");

    Char Buffer[MAX_PATH] = { 0 };
    CString WorkingDirectory = PathGetCurrentDirectory(Buffer, MAX_PATH);
    CString ConfigFilePath = PathCombineNoAlloc(WorkingDirectory, "MasterSvr.ini");
    ServerConfig Config = ServerConfigLoad(ConfigFilePath);

    AllocatorRef Allocator = AllocatorGetSystemDefault();
    struct _ServerContext ServerContext = { 0 };
    ServerContext.Config = Config;
    ServerContext.AuthSocket = NULL;
    ServerContext.WorldSocket = NULL;
    ServerContext.Database = NULL;
    ServerContext.WorldListBroadcastTimestamp = 0;
    ServerContext.WorldListUpdateTimestamp = 0;
    ServerContext.PartyPool = MemoryPoolCreate(Allocator, sizeof(struct _RTParty), Config.MasterSvr.MaxPartyCount);
    ServerContext.PartyTable = EntityDictionaryCreate(Allocator, Config.MasterSvr.MaxPartyCount);

    IPCNodeID NodeID = kIPCNodeIDNull;
    NodeID.Group = Config.MasterSvr.ServerID;
    NodeID.Index = 0;
    NodeID.Type = IPC_TYPE_MASTER;

    ServerRef Server = ServerCreate(
        Allocator,
        NodeID,
        NULL,
        Config.MasterSvr.Port,
        0,
        Config.NetLib.ReadBufferSize,
        Config.NetLib.WriteBufferSize,
        &ServerOnUpdate, 
        &ServerContext
    );

    ServerContext.AuthSocket = ServerCreateSocket(
        Server,
        SOCKET_FLAGS_IPC,
        Config.AuthSvr.Host,
        Config.AuthSvr.Port,
        sizeof(union _ClientContext),
        Config.NetLib.ProtocolIdentifier,
        Config.NetLib.ProtocolVersion,
        Config.NetLib.ProtocolExtension,
        Config.NetLib.ReadBufferSize,
        Config.NetLib.WriteBufferSize,
        1,
        &AuthSocketOnConnect,
        &AuthSocketOnDisconnect
    );
    
    ServerContext.WorldSocket = ServerCreateSocket(
        Server,
        SOCKET_FLAGS_LISTENER | SOCKET_FLAGS_IPC,
        NULL,
        Config.MasterSvr.Port,
        sizeof(union _ClientContext),
        Config.NetLib.ProtocolIdentifier,
        Config.NetLib.ProtocolVersion,
        Config.NetLib.ProtocolExtension,
        Config.NetLib.ReadBufferSize,
        Config.NetLib.WriteBufferSize,
        Config.MasterSvr.MaxWorldCount,
        &WorldSocketOnConnect,
        &WorldSocketOnDisconnect
    );

    ServerContext.Database = DatabaseConnect(
        Config.MasterDB.Host,
        Config.MasterDB.Username,
        Config.MasterDB.Password,
        Config.MasterDB.Database,
        Config.MasterDB.Port,
        Config.MasterDB.AutoReconnect
    );
    
    if (!ServerContext.Database) {
        FatalError("Database connection failed");
    }

    MasterDBPrepareStatements(ServerContext.Database);

#define IPC_AUTH_PROCEDURE(__NAME__, __COMMAND__, __PROTOCOL__) \
    ServerSocketRegisterPacketCallback(Server, ServerContext.AuthSocket, __COMMAND__, &SERVER_AUTH_ ## __NAME__);

#define IPC_WORLD_PROCEDURE(__NAME__, __COMMAND__, __PROTOCOL__) \
    ServerSocketRegisterPacketCallback(Server, ServerContext.WorldSocket, __COMMAND__, &SERVER_WORLD_ ## __NAME__);

#include "IPCProcDefinition.h"

    ServerRun(Server);
    ServerDestroy(Server);
    DatabaseDisconnect(ServerContext.Database);
    DiagnosticTeardown();

    return EXIT_SUCCESS;
}
