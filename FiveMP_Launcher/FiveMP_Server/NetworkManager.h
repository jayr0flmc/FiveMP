#pragma once
class SNetworkManager
{
public:
	SNetworkManager();
	~SNetworkManager();

	bool Start();
	void Pulse();
	void HandlePlayerSync(Packet *p);

	RPC4 rpc;
	DirectoryDeltaTransfer directoryDeltaTransfer;
	FileListTransfer fileListTransfer;

	RakNet::RakPeerInterface *server;
	RakNet::RakNetStatistics *rss;
	RakNet::Packet* packet;
	RakNet::SystemAddress clientID;
	RakNet::SocketDescriptor socketDescriptors[2];
	RakNet::ConnectionAttemptResult connection;

	bool Connected = false;
	bool Listening = false;
	bool Synchronized = false;

	int playerid;
	int time_hour;
	int time_minute;
	bool time_pause;

	char MsgLength[128];

	unsigned char GetPacketIdentifier(RakNet::Packet *p);
	unsigned char packetIdentifier;

	bool sync_test;
};