#pragma once
class CNetworkManager
{
public:
	CNetworkManager();
	~CNetworkManager();

	bool Connect(char *serveraddress, char *port, char *clientport);
	bool Disconnect();
	void Pulse();
	void HandlePlayerSync(Packet *p);

	void SyncOnFoot();

	RPC4 rpc;
	DirectoryDeltaTransfer directoryDeltaTransfer;
	FileListTransfer fileListTransfer;

	RakNet::RakPeerInterface *client;
	RakNet::Packet* packet;
	RakNet::SystemAddress clientID;
	RakNet::ConnectionAttemptResult connection;

	bool Connected = false;
	bool Listening = false;
	bool Synchronized = false;

	int playerid;
	int time_hour;
	int time_minute;
	bool time_pause;

	bool sync_test;
};

