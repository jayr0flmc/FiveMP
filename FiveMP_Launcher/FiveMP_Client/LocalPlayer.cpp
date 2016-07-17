#include "stdafx.h"

CLocalPlayer::CLocalPlayer()
{
	playerPed = PLAYER::PLAYER_PED_ID();
}

CLocalPlayer::~CLocalPlayer()
{
}

void CLocalPlayer::Initialize()
{
	if (!playerInitialized) {
		player.DisableScripts();
		SCRIPT::SHUTDOWN_LOADING_SCREEN();
		CAM::DO_SCREEN_FADE_IN(500);

		UI::DISPLAY_RADAR(true);
		UI::DISPLAY_HUD(true);

		for (int i = 0; i < 5; i++) {
			GAMEPLAY::DISABLE_HOSPITAL_RESTART(i, true);
		}

		playerInitialized = true;

		GAMEPLAY::SET_MISSION_FLAG(true);
		TIME::PAUSE_CLOCK(true);
	}
}

void CLocalPlayer::OnTick()
{
	VEHICLE::SET_GARBAGE_TRUCKS(false);
	VEHICLE::SET_RANDOM_BOATS(false);
	VEHICLE::SET_RANDOM_TRAINS(false);
	VEHICLE::SET_FAR_DRAW_VEHICLES(false);
	VEHICLE::_0xF796359A959DF65D(false);
	VEHICLE::DELETE_ALL_TRAINS();
	VEHICLE::SET_RANDOM_VEHICLE_DENSITY_MULTIPLIER_THIS_FRAME(0.0);
	VEHICLE::SET_NUMBER_OF_PARKED_VEHICLES(-1);
	VEHICLE::SET_ALL_LOW_PRIORITY_VEHICLE_GENERATORS_ACTIVE(false);
	VEHICLE::SET_VEHICLE_DENSITY_MULTIPLIER_THIS_FRAME(0.0);
	VEHICLE::REMOVE_VEHICLES_FROM_GENERATORS_IN_AREA(-9999.0f, -9999.0f, -9999.0f, 9999.0f, 9999.0f, 9999.0f, false);

	PED::SET_CREATE_RANDOM_COPS_NOT_ON_SCENARIOS(false);
	PED::SET_CREATE_RANDOM_COPS(false);
	PED::SET_CREATE_RANDOM_COPS_ON_SCENARIOS(false);
	PED::SET_PED_DENSITY_MULTIPLIER_THIS_FRAME(0.0f);
	PED::SET_SCENARIO_PED_DENSITY_MULTIPLIER_THIS_FRAME(0.0f, 0.0f);

	PLAYER::SET_MAX_WANTED_LEVEL(0);

	MOBILE::DESTROY_MOBILE_PHONE();

	STREAMING::SET_VEHICLE_POPULATION_BUDGET(0);
	STREAMING::SET_PED_POPULATION_BUDGET(0);

	CONTROLS::DISABLE_CONTROL_ACTION(2, 19, true);

	UI::_0x170F541E1CADD1DE(true);
	UI::SHOW_HUD_COMPONENT_THIS_FRAME(3);
	UI::DISPLAY_CASH(true);
}

Vector4 CLocalPlayer::GetQuaternion()
{
	Vector4 rotation;

	ENTITY::GET_ENTITY_QUATERNION(playerPed, &rotation.fX, &rotation.fY, &rotation.fZ, &rotation.fW);

	return rotation;
}

int CLocalPlayer::GetVehicle()
{
	if (PED::GET_VEHICLE_PED_IS_IN(playerPed, false) > 0) {
		for (int i = 0; i < 100; i++) {
			if (vehicleData[i].vehicleVehicle == PED::GET_VEHICLE_PED_IS_IN(playerPed, false)) {
				return vehicleData[i].vehicleid;
			}
		}
	}
	return -1;
}

int CLocalPlayer::GetVehicleSeat()
{
	if (PED::GET_VEHICLE_PED_IS_IN(playerPed, false) > 0) {
		return -1;
	}
	return 0;
}

void CLocalPlayer::SetModel(Hash model)
{
	int health = GetHealth();
	int armour = GetArmour();

	if (STREAMING::IS_MODEL_IN_CDIMAGE(model) && STREAMING::IS_MODEL_VALID(model))

		STREAMING::REQUEST_MODEL(model);
	while (!STREAMING::HAS_MODEL_LOADED(model))
		WAIT(0);
	PLAYER::SET_PLAYER_MODEL(0, model);
	STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(model);
	playerPed = PLAYER::GET_PLAYER_PED(0);

	SetHealth(health);
	SetArmour(armour);
}

void CLocalPlayer::SendOnFootData()
{
	RakNet::BitStream PlayerBitStream_send;

	PlayerBitStream_send.Write((MessageID)ID_SEND_PLAYER_DATA);

	PlayerBitStream_send.Write(NetworkManager->playerid);

	PlayerBitStream_send.Write(GetType());
	PlayerBitStream_send.Write(GetModel());
	PlayerBitStream_send.Write(GetHealth());
	PlayerBitStream_send.Write(GetArmour());

	PlayerBitStream_send.Write(GetCoords().x);
	PlayerBitStream_send.Write(GetCoords().y);
	PlayerBitStream_send.Write(GetCoords().z);

	PlayerBitStream_send.Write(GetHeading());
	PlayerBitStream_send.Write(GetQuaternion().fX);
	PlayerBitStream_send.Write(GetQuaternion().fY);
	PlayerBitStream_send.Write(GetQuaternion().fZ);
	PlayerBitStream_send.Write(GetQuaternion().fW);

	PlayerBitStream_send.Write(AI::GET_PED_DESIRED_MOVE_BLEND_RATIO(playerPed));
	PlayerBitStream_send.Write(GetVelocity().x);
	PlayerBitStream_send.Write(GetVelocity().y);
	PlayerBitStream_send.Write(GetVelocity().z);

	PlayerBitStream_send.Write(LocalPlayer->GetVehicle());
	PlayerBitStream_send.Write(LocalPlayer->GetVehicleSeat());

	PlayerBitStream_send.Write(time(0));

	NetworkManager->client->Send(&PlayerBitStream_send, MEDIUM_PRIORITY, UNRELIABLE_SEQUENCED, 0, RakNet::UNASSIGNED_SYSTEM_ADDRESS, true);
}

char* replaceCharacter(char* name, char char1, char char2) {
	for (int i = 0; i < sizeof(name); ++i) {
		if (name[i] == char1)
			name[i] = char2;
	}

	return name;
}

void CLocalPlayer::SendSyncRequest()
{
	if (time(0) - timesincerequest > 10) {
		RakNet::BitStream requestid;

		char* playerUsername = replaceCharacter(Config->client_username, '~', ' ');

		requestid.Write((MessageID)ID_REQUEST_SERVER_SYNC);
		requestid.Write(playerUsername);

		NetworkManager->client->Send(&requestid, HIGH_PRIORITY, RELIABLE_ORDERED, 0, RakNet::UNASSIGNED_SYSTEM_ADDRESS, true);

		player.ShowMessageAboveMap("Synchronizing with the server...");

		timesincerequest = time(0);
	}
}
