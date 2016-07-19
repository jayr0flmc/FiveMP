#include "stdafx.h"

CNetworkManager::CNetworkManager()
{
	client = RakNet::RakPeerInterface::GetInstance();
	clientID = RakNet::UNASSIGNED_SYSTEM_ADDRESS;
}

CNetworkManager::~CNetworkManager()
{
	Connected = false;
	Listening = false;
	Synchronized = false;

	playerid = -1;
	time_hour = NULL;
	time_minute = NULL;
	time_pause = NULL;

	RPCManager->UnRegisterRPCs();
}

bool CNetworkManager::Connect(char *serveraddress, char *port, char *clientport)
{
	if (serveraddress != NULL && port != NULL && clientport != NULL) {
		RakNet::SocketDescriptor socketDescriptor(atoi(clientport), 0);

		socketDescriptor.socketFamily = AF_INET;
		client->Startup(8, &socketDescriptor, 1);
		client->SetOccasionalPing(true);

		connection = client->Connect(serveraddress, atoi(port), "fivemp_dev", (int)strlen("fivemp_dev"));
		RakAssert(connection == RakNet::CONNECTION_ATTEMPT_STARTED);

		Listening = true;
		return true;
	}

	return false;
}

bool CNetworkManager::Disconnect()
{
	if (Listening) {
		client->Shutdown(300);

		Connected = false;
		Synchronized = false;
		Listening = false;
		return true;
	}

	return false;
}

void CNetworkManager::Pulse()
{
	for (packet = client->Receive(); packet; client->DeallocatePacket(packet), packet = client->Receive()) {
		unsigned char packetIdentifier = GetPacketIdentifier(packet);

		RakNet::BitStream playerClientID(packet->data+1, packet->length+1, false);

		RakNet::BitStream bsPlayerConnect;

		char testmessage[128];

		switch (packetIdentifier) {
		case ID_CONNECTION_REQUEST_ACCEPTED:
			Connected = true;

			sprintf(testmessage, "Hi ~b~%s~w~, you have successfully connected to the server!\n", Config->client_username);
			printf(testmessage);

			sprintf(testmessage, "GUID is: ~b~#%s\n", client->GetGuidFromSystemAddress(RakNet::UNASSIGNED_SYSTEM_ADDRESS).ToString());
			printf(testmessage);

			ASIManager->sysAddrZero = packet->systemAddress;
			break;

		case ID_CONNECTION_ATTEMPT_FAILED:
			Connected = false;
			Synchronized = false;

			Listening = false;
			break;

		case ID_NO_FREE_INCOMING_CONNECTIONS:
			Connected = false;
			Synchronized = false;

			printf("~r~Server is full!\n");
			Listening = false;
			break;

		case ID_DISCONNECTION_NOTIFICATION:
			Connected = false;
			Synchronized = false;

			printf("~r~Connection closed!\n");
			Listening = false;
			break;

		case ID_CONNECTION_LOST:
			Connected = false;
			Synchronized = false;

			printf("~r~Connection Lost!\n");
			Listening = false;
			break;

		case ID_CONNECTION_BANNED:
			Connected = false;
			Synchronized = false;

			printf("~r~You're banned from this server!\n");
			Listening = false;
			break;

		case ID_REQUEST_SERVER_SYNC:
			playerClientID.Read(playerid);

			playerClientID.Read(time_hour);
			playerClientID.Read(time_minute);
			playerClientID.Read(time_pause);

			bsPlayerConnect.Write(playerid);
			rpc.Signal("PlayerConnect", &bsPlayerConnect, HIGH_PRIORITY, RELIABLE_ORDERED, 0, RakNet::UNASSIGNED_SYSTEM_ADDRESS, true, false);

			NetworkManager->Synchronized = true;
			break;

		case ID_SEND_PLAYER_DATA:
			HandlePlayerSync(packet);
			break;

		case ID_PLAYER_LEFT:
			break;

		default:
			sprintf(testmessage, "%s\n", packet->data);
			printf(testmessage);

			sprintf(testmessage, "Exception from %s\n", packet->data);
			client->Send(testmessage, (int)strlen(testmessage) + 1, IMMEDIATE_PRIORITY, RELIABLE_ORDERED, 0, RakNet::UNASSIGNED_SYSTEM_ADDRESS, false);
			break;
		}
	}
}

void CNetworkManager::HandlePlayerSync(Packet * p)
{
	RakNet::BitStream PlayerBitStream_receive(p->data+1, p->length+1, false);

	int tempplyrid;

	time_t temptimestamp;

	PlayerBitStream_receive.Read(tempplyrid);

	playerData[tempplyrid].playerid = tempplyrid;

	playerData[tempplyrid].oldx = playerData[tempplyrid].x;
	playerData[tempplyrid].oldy = playerData[tempplyrid].y;
	playerData[tempplyrid].oldz = playerData[tempplyrid].z;

	PlayerBitStream_receive.Read(playerData[tempplyrid].pedHealth);
	PlayerBitStream_receive.Read(playerData[tempplyrid].pedHealth);
	PlayerBitStream_receive.Read(playerData[tempplyrid].pedHealth);

	PlayerBitStream_receive.Read(playerData[tempplyrid].playerusername);

	PlayerBitStream_receive.Read(playerData[tempplyrid].x);
	PlayerBitStream_receive.Read(playerData[tempplyrid].y);
	PlayerBitStream_receive.Read(playerData[tempplyrid].z);

	PlayerBitStream_receive.Read(playerData[tempplyrid].r);
	PlayerBitStream_receive.Read(playerData[tempplyrid].rx);
	PlayerBitStream_receive.Read(playerData[tempplyrid].ry);
	PlayerBitStream_receive.Read(playerData[tempplyrid].rz);
	PlayerBitStream_receive.Read(playerData[tempplyrid].rw);

	PlayerBitStream_receive.Read(playerData[tempplyrid].v);
	PlayerBitStream_receive.Read(playerData[tempplyrid].vx);
	PlayerBitStream_receive.Read(playerData[tempplyrid].vy);
	PlayerBitStream_receive.Read(playerData[tempplyrid].vz);

	PlayerBitStream_receive.Read(temptimestamp);
}