#include "stdafx.h"

int UserPool::AddToUserPool(char *username, RakNet::RakNetGUID guid)
{
	for (int i = 0; i < sizeof(playerData); i++)
	{
		if (playerData[i].used == false) {
			playerData[i].playerid				= i;
			playerData[i].playerusername		= std::string(username);
			playerData[i].playerguid			= guid;
			playerData[i].used					= true;

			printf("%s - %s\n", playerData[i].playerguid.ToString(), guid.ToString());
			return i;
		}
	}
	return -1;
}

void UserPool::RemoveFromUserPool(RakNet::RakNetGUID guid)
{
	for (int i = 0; i < sizeof(playerData); i++)
	{
		if (playerData[i].playerguid == guid) {
			playerData[i].used = false;
			return;
		}
	}
}

int UserPool::GetPlayerID(RakNet::RakNetGUID guid)
{
	for (int i = 0; i < sizeof(playerData); i++)
	{
		if (playerData[i].playerguid == guid) {
			return playerData[i].playerid;
		}
	}
	return -1;
}

const char *UserPool::GetPlayerUsername(RakNet::RakNetGUID guid)
{
	for (int i = 0; i < sizeof(playerData); i++)
	{
		if (playerData[i].playerguid == guid) {
			return playerData[i].playerusername.c_str();
		}
	}
}

RakNet::RakNetGUID UserPool::GetPlayerGUID(char *username)
{
	for (int i = 0; i < sizeof(playerData); i++)
	{
		if (playerData[i].playerusername == username) {
			return playerData[i].playerguid;
		}
	}
	return RakNet::UNASSIGNED_RAKNET_GUID;
}

RakNet::RakNetGUID UserPool::GetPlayerGUIDfromId(int playerid)
{
	for (int i = 0; i < sizeof(playerData); i++)
	{
		if (playerData[i].playerid == playerid) {
			return playerData[i].playerguid;
		}
	}
	return RakNet::UNASSIGNED_RAKNET_GUID;
}

int SpawnPointPool::AddToSpawnPool(float x, float y, float z)
{
	for (int i = 0; i < sizeof(spawnData); i++)
	{
		if (spawnData[i].used == false) {
			spawnData[i].spawnid = i;
			spawnData[i].x = x;
			spawnData[i].y = y;
			spawnData[i].z = z;
			spawnData[i].used = true;

			printf("Added Spawn Point %i at (%f, %f, %f) \n", i, x, y, z);
			return i;
		}
	}
	return -1;
}

void SpawnPointPool::RemoveFromSpawnPool(int spawnid)
{
	for (int i = 0; i < sizeof(spawnData); i++)
	{
		if (spawnData[i].spawnid == spawnid) {
			spawnData[i].used = false;
			return;
		}
	}
}

int VehiclePool::AddToVehiclePool(const char *modelname, float x, float y, float z, float heading, int color1, int color2, bool respawn, int respawndelay)
{
	for (int i = 0; i < sizeof(playerData); i++)
	{
		if (vehicleData[i].used == false) {
			vehicleData[i].used = true;
			vehicleData[i].vehicleid = i;
			vehicleData[i].spawnvehicleModel = modelname;
			vehicleData[i].x = x;
			vehicleData[i].y = y;
			vehicleData[i].z = z;
			vehicleData[i].r = heading;
			vehicleData[i].vehicleColor1 = color1;
			vehicleData[i].vehicleColor2 = color2;
			vehicleData[i].respawn = respawn;
			return i;
		}
	}
	return -1;
}

void VehiclePool::RemoveFromVehiclePool(int id)
{
	for (int i = 0; i < sizeof(vehicleData); i++)
	{
		if (vehicleData[i].vehicleid == id) {
			vehicleData[i].used = false;
			return;
		}
	}
}