#include "stdafx.h"

// -- WEAPON --
void ShowMessageToPlayer(RakNet::BitStream *bitStream, RakNet::Packet *packet) {
	int playerid;
	char string[128];

	bitStream->Read(playerid);
	bitStream->Read(string);

	player.ShowMessageAboveMap(string);
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

// -- MONEY --
void SetPlayerMoney(RakNet::BitStream* bitStream, RakNet::Packet *packet) {
	int playerid;
	int ammount;

	bitStream->Read(playerid);
	bitStream->Read(ammount);

	player.SetMoney(ammount);
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
}

void SetPlayerArmour(RakNet::BitStream * bitStream, RakNet::Packet * packet)
{
	int playerid;
	int armour;

	bitStream->Read(playerid);
	bitStream->Read(armour);
}
