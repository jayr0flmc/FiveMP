#include "stdafx.h"

// -- WEAPON --
void ShowMessageToPlayer(RakNet::BitStream *bitStream, RakNet::Packet *packet) {
	int playerid;
	char string[128];

	bitStream->Read(string);

	player.ShowMessageAboveMap(string);
}

void SendMessageToPlayer(RakNet::BitStream *bitStream, RakNet::Packet *packet) {
	int playerid;
	char string[128];
	color_t textColor;

	bitStream->Read(string);
	bitStream->Read(textColor);

	textColor = { 255, 255, 255, 255 };

	CChat::Get()->AddChatMessage(string, textColor);

	printf("%s\n", string);
}

void GivePlayerWeapon(RakNet::BitStream *bitStream, RakNet::Packet *packet) {
	int playerid;
	char weaponid[20];
	int ammo;

	bitStream->Read(playerid);
	bitStream->Read(weaponid);
	bitStream->Read(ammo);

	weapon.GiveWeapon(weaponid, ammo);
}

void RemovePlayerWeapon(RakNet::BitStream *bitStream, RakNet::Packet *packet) {
	int playerid;
	char weaponid[20];

	bitStream->Read(playerid);
	bitStream->Read(weaponid);

	weapon.RemoveWeapon(weaponid);
}

void GivePlayerAmmo(RakNet::BitStream *bitStream, RakNet::Packet *packet) {
	int playerid;
	char weaponid[20];
	int ammo;

	bitStream->Read(playerid);
	bitStream->Read(weaponid);
	bitStream->Read(ammo);

	weapon.GiveAmmo(weaponid, ammo);
}

void RemovePlayerAmmo(RakNet::BitStream *bitStream, RakNet::Packet *packet) {
	int playerid;
	char weaponid[20];
	int ammo;

	bitStream->Read(playerid);
	bitStream->Read(weaponid);
	bitStream->Read(ammo);

	weapon.RemoveAmmo(weaponid, ammo);
}

void RemovePlayerWeapons(RakNet::BitStream *bitStream, RakNet::Packet *packet) {
	int playerid;
	bitStream->Read(playerid);

	weapon.RemoveAllWeapons();
}

// -- MONEY --
void SetPlayerMoney(RakNet::BitStream* bitStream, RakNet::Packet *packet) {
	int playerid;
	int amount;

	bitStream->Read(playerid);
	bitStream->Read(amount);

	LocalPlayer->playerMoney = amount;
	UI::_SET_SINGLEPLAYER_HUD_CASH(amount, amount);

	for (int i = 0; i < 3; i++)
	{
		char statNameFull[32];
		sprintf_s(statNameFull, "SP%d_TOTAL_CASH", i);
		Hash hash = GAMEPLAY::GET_HASH_KEY(statNameFull);
		int val;
		STATS::STAT_GET_INT(hash, &val, -1);
		val = amount;
		STATS::STAT_SET_INT(hash, val, 1);
	}
}

// -- POSITION --
void SetPlayerPos(RakNet::BitStream* bitStream, RakNet::Packet *packet) {
	int playerid;
	float posx;
	float posy;
	float posz;

	bitStream->Read(playerid);
	bitStream->Read(posx);
	bitStream->Read(posy);
	bitStream->Read(posz);

	LocalPlayer->SetPos(posx, posy, posz);
}

void SetPlayerFacingAngle(RakNet::BitStream * bitStream, RakNet::Packet * packet)
{
	int playerid;
	float rotation;

	bitStream->Read(playerid);
	bitStream->Read(rotation);

	LocalPlayer->SetHeading(rotation);
}

void SetPlayerHealth(RakNet::BitStream * bitStream, RakNet::Packet * packet)
{
	int playerid;
	int health;

	bitStream->Read(playerid);
	bitStream->Read(health);

	LocalPlayer->SetHealth(health);
}

void SetPlayerArmour(RakNet::BitStream * bitStream, RakNet::Packet * packet)
{
	int playerid;
	int armour;

	bitStream->Read(playerid);
	bitStream->Read(armour);

	LocalPlayer->SetArmour(armour);
}

void SetPlayerMaxNickDrawDistance(RakNet::BitStream * bitStream, RakNet::Packet * packet) {
	int playerid;
	float distance;

	bitStream->Read(playerid);
	bitStream->Read(distance);

	LocalPlayer->maxNickDrawDistance = distance;
}

void SetPlayerModel(RakNet::BitStream * bitStream, RakNet::Packet * packet)
{
	int playerid;
	int modelid;

	bitStream->Read(playerid);
	bitStream->Read(modelid);

	LocalPlayer->SetModel(GetModelHashFromModelID(modelid));
}

void CreateVehicle(RakNet::BitStream * bitStream, RakNet::Packet * packet)
{
	int vehicleid;
	char vehiclename[32];

	bitStream->Read(vehicleid);
	
	vehicleData[vehicleid].vehicleid = vehicleid;

	bitStream->Read(vehiclename);
	bitStream->Read(vehicleData[vehicleid].x);
	bitStream->Read(vehicleData[vehicleid].y);
	bitStream->Read(vehicleData[vehicleid].z);
	bitStream->Read(vehicleData[vehicleid].r);
	bitStream->Read(vehicleData[vehicleid].vehicleColor1);
	bitStream->Read(vehicleData[vehicleid].vehicleColor2);
	bitStream->Read(vehicleData[vehicleid].respawn);
	bitStream->Read(vehicleData[vehicleid].respawndelay);

	Vector3 tempcoords;
	tempcoords.x = vehicleData[vehicleid].x;
	tempcoords.y = vehicleData[vehicleid].y;
	tempcoords.z = vehicleData[vehicleid].z;

	vehicle.CreateVehicle(vehicleid, vehiclename, tempcoords, vehicleData[vehicleid].r, vehicleData[vehicleid].vehicleColor1, vehicleData[vehicleid].vehicleColor2, vehicleData[vehicleid].respawn, vehicleData[vehicleid].respawndelay);
}

void RemoveVehicle(RakNet::BitStream * bitStream, RakNet::Packet * packet)
{
	int vehicleid;

	bitStream->Read(vehicleid);

	vehicle.RemoveVehicle(vehicleid);
}

void SetVehicleColor(RakNet::BitStream * bitStream, RakNet::Packet * packet)
{
	int vehicleid;
	int layer;
	int color;
	int painttype;

	bitStream->Read(vehicleid);
	bitStream->Read(layer);
	bitStream->Read(color);
	bitStream->Read(painttype);

	vehicle.SetVehicleColor(vehicleid, layer, color, painttype);
}

void SetVehicleCustomColor(RakNet::BitStream * bitStream, RakNet::Packet * packet)
{
	int vehicleid;
	int layer;
	int r, g, b;

	bitStream->Read(vehicleid);
	bitStream->Read(layer);
	bitStream->Read(r);
	bitStream->Read(g);
	bitStream->Read(b);

	vehicle.SetVehicleCustomColor(vehicleid, layer, r, g, b);
}

void SetVehicleNumberPlate(RakNet::BitStream * bitStream, RakNet::Packet * packet)
{
	int vehicleid;
	RakNet::RakString plate;

	bitStream->Read(vehicleid);
	bitStream->Read(plate);

	vehicle.SetVehicleNumberPlate(vehicleid, plate.C_String());
}

void SetPedComponentVariation(RakNet::BitStream * bitStream, RakNet::Packet * packet)
{
	int playerid;
	int componentid;
	int drawableid;
	int textureid;
	int paletteid;

	bitStream->Read(playerid);
	bitStream->Read(componentid);
	bitStream->Read(drawableid);
	bitStream->Read(textureid);
	bitStream->Read(paletteid);

	PED::SET_PED_COMPONENT_VARIATION(LocalPlayer->playerPed, componentid, drawableid, textureid, paletteid);
}

void ShowBlipForPlayer(RakNet::BitStream * bitStream, RakNet::Packet * packet)
{
	int blipid;
	int locationtype;
	float x;
	float y;
	float z;
	int attachID;
	int color;
	int spriteid;
	RakNet::RakString string;

	bitStream->Read(blipid);
	bitStream->Read(locationtype);
	bitStream->Read(x);
	bitStream->Read(y);
	bitStream->Read(z);
	bitStream->Read(attachID);
	bitStream->Read(color);
	bitStream->Read(spriteid);
	bitStream->Read(string);

	CreateBlip(blipid, locationtype, x, y, z, attachID, color, spriteid, string.C_String());
}

void HideBlipFromPlayer(RakNet::BitStream * bitStream, RakNet::Packet * packet)
{
	int blipid;

	bitStream->Read(blipid);

	for (int i = 0; i < 100; i++) {
		if (blipData[i].serverID == blipid) {
			UI::REMOVE_BLIP(&blipData[i].blip);
			blipData[i].used = false;
			break;
		}
	}
}

void SetTime(RakNet::BitStream *bitStream, RakNet::Packet *packet) {
	int hour;
	int minute;
	int seconds;
	bitStream->Read(hour);
	bitStream->Read(minute);
	bitStream->Read(seconds);

	world.SetTime(hour, minute, seconds);
}

void RemoveDefaultBlipForPlayer(RakNet::BitStream * bitStream, RakNet::Packet * packet)
{
	int playerid;

	bitStream->Read(playerid);

	playerData[playerid].isDefaultBlipRemoved = true;

	if (UI::DOES_BLIP_EXIST(playerData[playerid].pedBlip)) {
		UI::REMOVE_BLIP(&playerData[playerid].pedBlip);
	}
}

void ShowPickupForPlayer(RakNet::BitStream * bitStream, RakNet::Packet * packet)
{
	int pickupid;
	float x;
	float y;
	float z;
	int interval;
	RakNet::RakString model;

	bitStream->Read(pickupid);
	bitStream->Read(model);
	bitStream->Read(x);
	bitStream->Read(y);
	bitStream->Read(z);
	bitStream->Read(interval);

	CreatePickup(pickupid, model.C_String(), x, y, z, interval);
}

void HidePickupForPlayer(RakNet::BitStream * bitStream, RakNet::Packet * packet)
{
	int pickupid;

	bitStream->Read(pickupid);

	for (int i = 0; i < 100; i++) {
		if (pickupData[i].used && pickupData[i].serverID == pickupid) {
			
			OBJECT::REMOVE_PICKUP(pickupData[i].pickup);
			pickupData[i].serverID = 0;
			pickupData[i].pickup = 0;
			pickupData[i].used = false;
			break;

		}
	}

}

void SetPlayerControlable(RakNet::BitStream * bitStream, RakNet::Packet * packet)
{
	int playerid;
	bool value;

	bitStream->Read(playerid);
	bitStream->Read(value);

	ENTITY::FREEZE_ENTITY_POSITION(LocalPlayer->playerPed, !value);
}
