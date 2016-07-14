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
	LocalPlayer->playerMoney = 0;

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
		LocalPlayer->timesincerequest = 0;
		LocalPlayer->playerMoney = 0;

		world.CleanUp();

		player.ShowMessageAboveMap("Successfully disconnected!");
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

			ENTITY::FREEZE_ENTITY_POSITION(LocalPlayer->playerPed, 0);
			ENTITY::SET_ENTITY_VISIBLE(LocalPlayer->playerPed, true, 0);
			break;

		case ID_CONNECTION_ATTEMPT_FAILED:
			Connected = false;
			Synchronized = false;
			LocalPlayer->playerMoney = 0;

			player.ShowMessageAboveMap("~r~Could not connect to the server");
			Listening = false;
			break;

		case ID_NO_FREE_INCOMING_CONNECTIONS:
			Connected = false;
			Synchronized = false;
			LocalPlayer->playerMoney = 0;

			player.ShowMessageAboveMap("~r~Server is full!");
			Listening = false;
			break;

		case ID_DISCONNECTION_NOTIFICATION:
			Connected = false;
			Synchronized = false;
			LocalPlayer->playerMoney = 0;

			player.ShowMessageAboveMap("~r~Connection closed!");
			Listening = false;

			world.CleanUp();
			break;

		case ID_CONNECTION_LOST:
			Connected = false;
			Synchronized = false;
			LocalPlayer->playerMoney = 0;

			player.ShowMessageAboveMap("~r~Connection Lost!");
			Listening = false;

			world.CleanUp();
			break;

		case ID_CONNECTION_BANNED:
			Connected = false;
			Synchronized = false;
			LocalPlayer->playerMoney = 0;

			player.ShowMessageAboveMap("~r~You're banned from this server!");
			Listening = false;

			world.CleanUp();
			break;

		case ID_REQUEST_SERVER_SYNC:
			playerClientID.Read(playerid);

			playerClientID.Read(time_hour);
			playerClientID.Read(time_minute);
			playerClientID.Read(time_pause);

			TIME::SET_CLOCK_TIME(time_hour, time_minute, 00);
			TIME::PAUSE_CLOCK(time_pause);

			bsPlayerConnect.Write(playerid);
			rpc.Signal("PlayerConnect", &bsPlayerConnect, HIGH_PRIORITY, RELIABLE_ORDERED, 0, UNASSIGNED_SYSTEM_ADDRESS, true, false);

			NetworkManager->Synchronized = true;
			break;

		case ID_SEND_PLAYER_DATA:
			HandlePlayerSync(packet);
			break;

		case ID_PLAYER_LEFT:
			DropPlayer(packet);
			break;

		default:
			sprintf(testmessage, "%s", packet->data);
			player.ShowMessageAboveMap(testmessage);

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

	Hash oldModel = playerData[tempplyrid].pedModel;

	PlayerBitStream_receive.Read(playerData[tempplyrid].pedType);
	PlayerBitStream_receive.Read(playerData[tempplyrid].pedModel);
	PlayerBitStream_receive.Read(playerData[tempplyrid].pedHealth);
	PlayerBitStream_receive.Read(playerData[tempplyrid].pedArmour);

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

	playerData[tempplyrid].tickssince = clock();

	//NO MORE OF SPAMMING THE CONSOLE :D
	//printf("received packet\n");

	//if (tempplyrid != playerid) {
		if (ENTITY::DOES_ENTITY_EXIST(playerData[tempplyrid].pedPed)) {

			if (oldModel != playerData[tempplyrid].pedModel) {
				UpdatePedModel(tempplyrid);
			}

			/*float tempz;

			GAMEPLAY::GET_GROUND_Z_FOR_3D_COORD(playerData[tempplyrid].x, playerData[tempplyrid].y, playerData[tempplyrid].z, &tempz, 1);

			if (SYSTEM::VDIST(playerData[tempplyrid].x, playerData[tempplyrid].y, playerData[tempplyrid].z, playerData[tempplyrid].x, playerData[tempplyrid].y, tempz) > 5.0f) {
				ENTITY::SET_ENTITY_COORDS(playerData[tempplyrid].pedPed, playerData[tempplyrid].x, playerData[tempplyrid].y, playerData[tempplyrid].z, 0, 0, 0, 0);
			}
			else {
				ENTITY::SET_ENTITY_COORDS(playerData[tempplyrid].pedPed, playerData[tempplyrid].x, playerData[tempplyrid].y, tempz, 0, 0, 0, 0);
				//AI::TASK_GO_STRAIGHT_TO_COORD(playerData[tempplyrid].pedPed, playerData[tempplyrid].x, playerData[tempplyrid].y, playerData[tempplyrid].z, playerData[tempplyrid].v, 1, playerData[tempplyrid].r, 0.0f);
			}
			ENTITY::SET_ENTITY_QUATERNION(playerData[tempplyrid].pedPed, playerData[tempplyrid].rx, playerData[tempplyrid].ry, playerData[tempplyrid].rz, playerData[tempplyrid].rw);*/
		} else {
			if (STREAMING::IS_MODEL_IN_CDIMAGE(playerData[tempplyrid].pedModel) && STREAMING::IS_MODEL_VALID(playerData[tempplyrid].pedModel))

				STREAMING::REQUEST_MODEL(playerData[tempplyrid].pedModel);
			while (!STREAMING::HAS_MODEL_LOADED(playerData[tempplyrid].pedModel))
				WAIT(0);
			playerData[tempplyrid].pedPed = PED::CREATE_PED(playerData[tempplyrid].pedType, playerData[tempplyrid].pedModel, playerData[tempplyrid].x, playerData[tempplyrid].y, playerData[tempplyrid].z, 0.0f, false, true);
			STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(playerData[tempplyrid].pedModel);

			ENTITY::SET_ENTITY_NO_COLLISION_ENTITY(LocalPlayer->playerPed, playerData[tempplyrid].pedPed, false);
			ENTITY::SET_ENTITY_NO_COLLISION_ENTITY(playerData[tempplyrid].pedPed, LocalPlayer->playerPed, false);

			PED::SET_PED_FLEE_ATTRIBUTES(playerData[tempplyrid].pedPed, 0, 0);
			PED::SET_PED_COMBAT_ATTRIBUTES(playerData[tempplyrid].pedPed, 17, 1);
			PED::SET_PED_CAN_RAGDOLL(playerData[tempplyrid].pedPed, false);

			AI::TASK_SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(playerData[tempplyrid].pedPed, true);

			playerData[tempplyrid].pedBlip = UI::ADD_BLIP_FOR_ENTITY(playerData[tempplyrid].pedPed);
			UI::SET_BLIP_AS_FRIENDLY(playerData[tempplyrid].pedBlip, true);
			UI::SET_BLIP_COLOUR(playerData[tempplyrid].pedBlip, 0);
			UI::SET_BLIP_SCALE(playerData[tempplyrid].pedBlip, 1.0f);
			UI::BEGIN_TEXT_COMMAND_SET_BLIP_NAME("STRING");
			UI::_ADD_TEXT_COMPONENT_STRING3(playerData[tempplyrid].playerusername);
			UI::END_TEXT_COMMAND_SET_BLIP_NAME(playerData[tempplyrid].pedBlip);
		}
	//}
}

float ttlerp(float v0, float v1, float t) {
	return (1 - t)*v0 + t*v1;
}

void CNetworkManager::SyncOnFoot()
{
	for (int i = 0; i < 10; i++) {
		if (ENTITY::DOES_ENTITY_EXIST(playerData[i].pedPed)) {
			if (sync_test == true) {
				CVector3 curpos1;
				curpos1.fX = playerData[i].oldx;
				curpos1.fY = playerData[i].oldy;
				curpos1.fZ = playerData[i].oldz;

				CVector3 newpos;
				newpos.fX = playerData[i].x;
				newpos.fY = playerData[i].y;
				newpos.fZ = playerData[i].z;

				clock_t now = clock();
				float elapsedTime = now - playerData[i].tickssince;
				float progress = elapsedTime / 15.6f;

				if (progress <= 1.0) {
					CVector3 updpos;
					updpos.fX = ttlerp(curpos1.fX, newpos.fX, progress);
					updpos.fY = ttlerp(curpos1.fY, newpos.fY, progress);
					updpos.fZ = ttlerp(curpos1.fZ, newpos.fZ, progress);

					printf("%f | %f | %f/%f/%f\n", elapsedTime, progress, updpos.fX, updpos.fY, updpos.fZ);

					ENTITY::SET_ENTITY_COORDS(playerData[i].pedPed, updpos.fX, updpos.fY, updpos.fZ, 0, 0, 0, 0);
					ENTITY::SET_ENTITY_QUATERNION(playerData[i].pedPed, playerData[i].rx, playerData[i].ry, playerData[i].rz, playerData[i].rw);
				}
				else {
					printf("packet updated too quickly!\n");
				}
			}
			else {
				ENTITY::SET_ENTITY_COORDS(playerData[i].pedPed, playerData[i].x, playerData[i].y, playerData[i].z, 0, 0, 0, 0);
				ENTITY::SET_ENTITY_QUATERNION(playerData[i].pedPed, playerData[i].rx, playerData[i].ry, playerData[i].rz, playerData[i].rw);
			}
		}
	}
}

void CNetworkManager::DropPlayer(Packet * p)
{
	RakNet::BitStream PlayerBitStream_receive(p->data + 1, p->length + 1, false);

	int tempplyrid;
	char tempplyrname[30];

	PlayerBitStream_receive.Read(tempplyrid);
	PlayerBitStream_receive.Read(tempplyrname);

	if (ENTITY::DOES_ENTITY_EXIST(playerData[tempplyrid].pedPed))
	{
		char sendmessage[128];

		ENTITY::DELETE_ENTITY(&playerData[tempplyrid].pedPed);
		UI::REMOVE_BLIP(&playerData[tempplyrid].pedBlip);

		sprintf(sendmessage, "~b~%s(%d)~w~ has left the server.", tempplyrname, tempplyrid);
		player.ShowMessageAboveMap(sendmessage);
	}
}
