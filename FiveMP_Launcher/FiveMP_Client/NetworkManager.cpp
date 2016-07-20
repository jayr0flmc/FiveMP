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

		CChat::Get()->Clear();
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
			playerClientID.Read(weather);

			TIME::SET_CLOCK_TIME(time_hour, time_minute, 00);
			TIME::PAUSE_CLOCK(time_pause);
			GAMEPLAY::SET_WEATHER_TYPE_PERSIST(weather);

			bsPlayerConnect.Write(playerid);
			rpc.Signal("PlayerConnect", &bsPlayerConnect, HIGH_PRIORITY, RELIABLE_ORDERED, 0, UNASSIGNED_SYSTEM_ADDRESS, true, false);

			NetworkManager->Synchronized = true;
			LocalPlayer->playerID = playerid;

			playerData[playerid].used = true;

			//ASIManager->Request();
			break;

		case ID_SEND_PLAYER_DATA:
			HandlePlayerSync(packet);
			break;

		case ID_SEND_VEHICLE_DATA:
			HandleVehicleSync(packet);
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

	PlayerBitStream_receive.Read(playerData[tempplyrid].vehicleid);
	PlayerBitStream_receive.Read(playerData[tempplyrid].vehicleseat);

	PlayerBitStream_receive.Read(temptimestamp);

	playerData[tempplyrid].tickssince = clock();

	if (!ENTITY::DOES_ENTITY_EXIST(playerData[tempplyrid].pedPed)) {
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

		if (!playerData[tempplyrid].isDefaultBlipRemoved) {
			playerData[tempplyrid].pedBlip = UI::ADD_BLIP_FOR_ENTITY(playerData[tempplyrid].pedPed);
			UI::SET_BLIP_AS_FRIENDLY(playerData[tempplyrid].pedBlip, true);
			UI::SET_BLIP_COLOUR(playerData[tempplyrid].pedBlip, 0);
			UI::SET_BLIP_SCALE(playerData[tempplyrid].pedBlip, 1.0f);
			UI::BEGIN_TEXT_COMMAND_SET_BLIP_NAME("STRING");
			UI::_ADD_TEXT_COMPONENT_STRING3(playerData[tempplyrid].playerusername);
			UI::END_TEXT_COMMAND_SET_BLIP_NAME(playerData[tempplyrid].pedBlip);
		}
	}
	else if (oldModel != playerData[tempplyrid].pedModel) {
		UpdatePedModel(tempplyrid);
	}
}

void CNetworkManager::HandleVehicleSync(Packet * p)
{
	RakNet::BitStream VehicleBitStream_receive(p->data + 1, p->length + 1, false);

	int tempvehicleid;
	time_t temptimestamp;

	VehicleBitStream_receive.Read(tempvehicleid);

	vehicleData[tempvehicleid].oldx = vehicleData[tempvehicleid].x;
	vehicleData[tempvehicleid].oldy = vehicleData[tempvehicleid].y;
	vehicleData[tempvehicleid].oldz = vehicleData[tempvehicleid].z;

	VehicleBitStream_receive.Read(vehicleData[tempvehicleid].vehicleModel);
	VehicleBitStream_receive.Read(vehicleData[tempvehicleid].vehicleHealth);

	VehicleBitStream_receive.Read(vehicleData[tempvehicleid].x);
	VehicleBitStream_receive.Read(vehicleData[tempvehicleid].y);
	VehicleBitStream_receive.Read(vehicleData[tempvehicleid].z);

	VehicleBitStream_receive.Read(vehicleData[tempvehicleid].r);
	VehicleBitStream_receive.Read(vehicleData[tempvehicleid].rx);
	VehicleBitStream_receive.Read(vehicleData[tempvehicleid].ry);
	VehicleBitStream_receive.Read(vehicleData[tempvehicleid].rz);
	VehicleBitStream_receive.Read(vehicleData[tempvehicleid].rw);

	VehicleBitStream_receive.Read(vehicleData[tempvehicleid].vx);
	VehicleBitStream_receive.Read(vehicleData[tempvehicleid].vy);
	VehicleBitStream_receive.Read(vehicleData[tempvehicleid].vz);

	VehicleBitStream_receive.Read(vehicleData[tempvehicleid].playerid);

	VehicleBitStream_receive.Read(temptimestamp);

	vehicleData[tempvehicleid].tickssince = clock();
}

float ttlerp(float v0, float v1, float t) {
	return (1 - t)*v0 + t*v1;
}

void CNetworkManager::SyncOnFoot()
{
	for (int i = 0; i < 25; i++) {
		if (ENTITY::DOES_ENTITY_EXIST(playerData[i].pedPed)) {
			if (sync_test == true && playerData[i].vehicleid < 0) {
				if (PED::IS_PED_IN_VEHICLE(playerData[vehicleData[i].playerid].pedPed, vehicleData[i].vehicleVehicle, false)) {
					AI::TASK_LEAVE_VEHICLE(playerData[i].pedPed, vehicleData[playerData[i].vehicleid].vehicleVehicle, 16);
				}

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

					//printf("%f | %f | %f/%f/%f\n", elapsedTime, progress, updpos.fX, updpos.fY, updpos.fZ);

					ENTITY::SET_ENTITY_COORDS(playerData[i].pedPed, updpos.fX, updpos.fY, updpos.fZ, 0, 0, 0, 0);
					ENTITY::SET_ENTITY_QUATERNION(playerData[i].pedPed, playerData[i].rx, playerData[i].ry, playerData[i].rz, playerData[i].rw);
				}
			} else {
				//ENTITY::SET_ENTITY_COORDS(playerData[i].pedPed, playerData[i].x, playerData[i].y, playerData[i].z, 0, 0, 0, 0);
				//ENTITY::SET_ENTITY_QUATERNION(playerData[i].pedPed, playerData[i].rx, playerData[i].ry, playerData[i].rz, playerData[i].rw);
			}
		}
	}
}

void CNetworkManager::SyncVehicle()
{
	for (int i = 0; i < 25; i++) {
		if (ENTITY::DOES_ENTITY_EXIST(vehicleData[i].vehicleVehicle)) {
			if (vehicleData[i].vehicleid != playerData[LocalPlayer->playerID].vehicleid) {
				if (sync_test == true) {
					if (!PED::IS_PED_IN_VEHICLE(playerData[vehicleData[i].playerid].pedPed, vehicleData[i].vehicleVehicle, false) && vehicleData[i].playerid >= 0) {
						PED::SET_PED_INTO_VEHICLE(playerData[vehicleData[i].playerid].pedPed, vehicleData[i].vehicleVehicle, -1);
					}

					CVector3 curpos1;
					curpos1.fX = vehicleData[i].oldx;
					curpos1.fY = vehicleData[i].oldy;
					curpos1.fZ = vehicleData[i].oldz;

					CVector3 newpos;
					newpos.fX = vehicleData[i].x;
					newpos.fY = vehicleData[i].y;
					newpos.fZ = vehicleData[i].z;

					clock_t now = clock();
					clock_t elapsedTime = now - vehicleData[i].tickssince;
					double progress = elapsedTime / 15.6f;

					if (progress <= 1.0) {
						CVector3 updpos;
						updpos.fX = ttlerp(curpos1.fX, newpos.fX, progress);
						updpos.fY = ttlerp(curpos1.fY, newpos.fY, progress);
						updpos.fZ = ttlerp(curpos1.fZ, newpos.fZ, progress);

						//printf("%f | %f | %f/%f/%f\n", elapsedTime, progress, updpos.fX, updpos.fY, updpos.fZ);

						ENTITY::SET_ENTITY_COORDS(vehicleData[i].vehicleVehicle, updpos.fX, updpos.fY, updpos.fZ, 0, 0, 0, 0);
						ENTITY::SET_ENTITY_QUATERNION(vehicleData[i].vehicleVehicle, vehicleData[i].rx, vehicleData[i].ry, vehicleData[i].rz, vehicleData[i].rw);
					}
					vehicleData[i].playerid = -1;
				} else {
					printf("WARNING: interpolation disabled!\n");

					if (!PED::IS_PED_IN_VEHICLE(playerData[vehicleData[i].playerid].pedPed, vehicleData[i].vehicleVehicle, false) && vehicleData[i].playerid >= 0)
						PED::SET_PED_INTO_VEHICLE(playerData[vehicleData[i].playerid].pedPed, vehicleData[i].vehicleVehicle, -1);

					ENTITY::SET_ENTITY_COORDS(vehicleData[i].vehicleVehicle, vehicleData[i].x, vehicleData[i].y, vehicleData[i].z, 0, 0, 0, 0);
					ENTITY::SET_ENTITY_QUATERNION(vehicleData[i].vehicleVehicle, vehicleData[i].rx, vehicleData[i].ry, vehicleData[i].rz, vehicleData[i].rw);
				}
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

	if (ENTITY::DOES_ENTITY_EXIST(playerData[tempplyrid].pedPed)) {
		char sendmessage[128];

		AI::TASK_LEAVE_VEHICLE(playerData[tempplyrid].pedPed, vehicleData[playerData[tempplyrid].vehicleid].vehicleVehicle, 16);

		playerData[tempplyrid].vehicleid = -1;

		PED::DELETE_PED(&playerData[tempplyrid].pedPed);
		ENTITY::DELETE_ENTITY(&playerData[tempplyrid].pedPed);
		UI::REMOVE_BLIP(&playerData[tempplyrid].pedBlip);

		playerData[tempplyrid].used = false;
	}
}
