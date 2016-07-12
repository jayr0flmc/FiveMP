#include "stdafx.h"

SNetworkManager::SNetworkManager()
{
	server = RakNet::RakPeerInterface::GetInstance();
	clientID = RakNet::UNASSIGNED_SYSTEM_ADDRESS;
}

SNetworkManager::~SNetworkManager()
{
	Connected = false;
	Listening = false;
	Synchronized = false;

	playerid = -1;
	time_hour = NULL;
	time_minute = NULL;
	time_pause = NULL;

	RPCManager->UnRegisterRPCs();

	server->Shutdown(300);
	RakNet::RakPeerInterface::DestroyInstance(server);
}

bool SNetworkManager::Start()
{
	if (Config->MaxPlayers != NULL && Config->ServerPort != NULL) {
		socketDescriptors[0].port = atoi(Config->ServerPort);
		socketDescriptors[0].socketFamily = AF_INET; // Test out IPV4
		socketDescriptors[1].port = atoi(Config->ServerPort);
		socketDescriptors[1].socketFamily = AF_INET6; // Test out IPV6
		bool b = server->Startup(Config->MaxPlayers, socketDescriptors, 2) == RakNet::RAKNET_STARTED;
		server->SetMaximumIncomingConnections(Config->MaxPlayers);
		if (!b)
		{
			b = server->Startup(Config->MaxPlayers, socketDescriptors, 1) == RakNet::RAKNET_STARTED;
			if (!b)
			{
				puts("Server failed to start.  Terminating.");
				exit(1);
			}
		}

		server->SetIncomingPassword("fivemp_dev", (int)strlen("fivemp_dev"));
		server->SetTimeoutTime(15000, RakNet::UNASSIGNED_SYSTEM_ADDRESS);

		Listening = true;
		return true;
	}

	return false;
}

void SNetworkManager::Pulse()
{
	RakSleep(15.6);

	for (packet = server->Receive(); packet; server->DeallocatePacket(packet), packet = server->Receive())
	{
		packetIdentifier = GetPacketIdentifier(packet);

		RakNet::BitStream pid_bitStream;
		RakNet::BitStream pid_request(packet->data + 1, 128, false);

		RakNet::BitStream PlayerBitStream_send;
		RakNet::BitStream PlayerBitStream_receive(packet->data + 1, 128, false);

		RakNet::RakString tempusername;

		switch (packetIdentifier)
		{
		case ID_DISCONNECTION_NOTIFICATION:
			printf("ID_DISCONNECTION_NOTIFICATION from %s\n", packet->systemAddress.ToString(true));;
			OnPlayerDisconnect(sLUA, netPool.GetPlayerID(packet->guid));

			tempusername = netPool.GetPlayerUsername(packet->guid);

			pid_bitStream.Write((unsigned char)ID_PLAYER_LEFT);
			pid_bitStream.Write(netPool.GetPlayerID(packet->guid));
			pid_bitStream.Write(tempusername);

			server->Send(&pid_bitStream, HIGH_PRIORITY, RELIABLE_ORDERED, 0, RakNet::UNASSIGNED_SYSTEM_ADDRESS, true);

			netPool.RemoveFromUserPool(packet->guid);
			netPool.UserAmount--;
			break;

		case ID_NEW_INCOMING_CONNECTION:
			printf("Incoming connection (IP|PORT: %s - GUID: %s)\n", packet->systemAddress.ToString(true), packet->guid.ToString());
			clientID = packet->systemAddress;

			netPool.UserAmount++;
			break;

		case ID_REQUEST_SERVER_SYNC:
			printf("wake up fag\n");

			char tempname[64];
			int tempid;

			pid_request.Read(tempname);

			tempid = netPool.AddToUserPool(tempname, packet->guid);

			pid_bitStream.Write((unsigned char)ID_REQUEST_SERVER_SYNC);

			pid_bitStream.Write(tempid);

			pid_bitStream.Write(Config->ServerTimeHour);
			pid_bitStream.Write(Config->ServerTimeMinute);
			pid_bitStream.Write(Config->ServerTimeFreeze);

			server->Send(&pid_bitStream, HIGH_PRIORITY, RELIABLE_ORDERED, 0, packet->systemAddress, false);
			break;

		case ID_SEND_PLAYER_DATA:
			// Receive data
			int tempplyrid;
			time_t temptimestamp;

			PlayerBitStream_receive.Read(tempplyrid);

			PlayerBitStream_receive.Read(playerData[tempplyrid].pedType);
			PlayerBitStream_receive.Read(playerData[tempplyrid].pedModel);
			PlayerBitStream_receive.Read(playerData[tempplyrid].pedHealth);

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

			// Send to other users.

			PlayerBitStream_send.Write((unsigned char)ID_SEND_PLAYER_DATA);

			PlayerBitStream_send.Write(tempplyrid);

			PlayerBitStream_send.Write(playerData[tempplyrid].pedType);
			PlayerBitStream_send.Write(playerData[tempplyrid].pedModel);
			PlayerBitStream_send.Write(playerData[tempplyrid].pedHealth);

			if (playerData[tempplyrid].playerusername != NULL)
				PlayerBitStream_send.Write(playerData[tempplyrid].playerusername);
			else {
				RakNet::RakString playername = "Player";
				PlayerBitStream_send.Write(playername);
			}

			PlayerBitStream_send.Write(playerData[tempplyrid].x);
			PlayerBitStream_send.Write(playerData[tempplyrid].y);
			PlayerBitStream_send.Write(playerData[tempplyrid].z);

			PlayerBitStream_send.Write(playerData[tempplyrid].r);
			PlayerBitStream_send.Write(playerData[tempplyrid].rx);
			PlayerBitStream_send.Write(playerData[tempplyrid].ry);
			PlayerBitStream_send.Write(playerData[tempplyrid].rz);
			PlayerBitStream_send.Write(playerData[tempplyrid].rw);

			PlayerBitStream_send.Write(playerData[tempplyrid].v);
			PlayerBitStream_send.Write(playerData[tempplyrid].vx);
			PlayerBitStream_send.Write(playerData[tempplyrid].vy);
			PlayerBitStream_send.Write(playerData[tempplyrid].vz);

			PlayerBitStream_send.Write(temptimestamp);

			server->Send(&PlayerBitStream_send, HIGH_PRIORITY, RELIABLE_ORDERED, 0, packet->systemAddress, true);

			//printf("%s | %d - %x | %f, %f, %f | %f, %f, %f, %f\n", playerData[tempplyrid].playerusername, playerData[tempplyrid].pedType, playerData[tempplyrid].pedModel, playerData[tempplyrid].x, playerData[tempplyrid].y, playerData[tempplyrid].z, playerData[tempplyrid].rx, playerData[tempplyrid].ry, playerData[tempplyrid].rz, playerData[tempplyrid].rw);
			break;

		case ID_INCOMPATIBLE_PROTOCOL_VERSION:
			printf("ID_INCOMPATIBLE_PROTOCOL_VERSION\n");
			break;

		case ID_CONNECTED_PING:
		case ID_UNCONNECTED_PING:
			printf("Ping from %s\n", packet->systemAddress.ToString(true));
			break;

		case ID_CONNECTION_LOST:
			printf("ID_CONNECTION_LOST from %s\n", packet->systemAddress.ToString(true));;
			OnPlayerDisconnect(sLUA, netPool.GetPlayerID(packet->guid));

			pid_bitStream.Write((unsigned char)ID_PLAYER_LEFT);
			pid_bitStream.Write(netPool.GetPlayerID(packet->guid));

			server->Send(&pid_bitStream, HIGH_PRIORITY, RELIABLE_ORDERED, 0, RakNet::UNASSIGNED_SYSTEM_ADDRESS, true);

			netPool.UserAmount--;
			netPool.RemoveFromUserPool(packet->guid);
			break;

		default:
			printf("%s\n", packet->data);

			sprintf(MsgLength, "%s", packet->data);
			server->Send(MsgLength, (const int)strlen(MsgLength) + 1, HIGH_PRIORITY, RELIABLE_ORDERED, 0, packet->systemAddress, true);

			break;
		}
	}
}

void SNetworkManager::HandlePlayerSync(Packet * p)
{
	/*RakNet::BitStream PlayerBitStream_receive(p->data + 1, p->length + 1, false);

	int tempplyrid;

	time_t temptimestamp;

	PlayerBitStream_receive.Read(tempplyrid);

	playerData[tempplyrid].playerid = tempplyrid;

	playerData[tempplyrid].oldx = playerData[tempplyrid].x;
	playerData[tempplyrid].oldy = playerData[tempplyrid].y;
	playerData[tempplyrid].oldz = playerData[tempplyrid].z;

	PlayerBitStream_receive.Read(playerData[tempplyrid].pedType);
	PlayerBitStream_receive.Read(playerData[tempplyrid].pedModel);
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

	*/
}

unsigned char SNetworkManager::GetPacketIdentifier(RakNet::Packet *p)
{
	if (p == 0)
		return 255;

	if ((unsigned char)p->data[0] == ID_TIMESTAMP)
	{
		RakAssert(p->length > sizeof(RakNet::MessageID) + sizeof(RakNet::Time));
		return (unsigned char)p->data[sizeof(RakNet::MessageID) + sizeof(RakNet::Time)];
	}
	else
		return (unsigned char)p->data[0];
}