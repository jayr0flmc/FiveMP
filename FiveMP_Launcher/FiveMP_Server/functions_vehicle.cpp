#include "stdafx.h"

int CreateVehicle(lua_State* state)
{
	int args = lua_gettop(state);

	printf("CreateVehicle() was called with %d arguments:\n", args);

	int playerid = lua_tointeger(state, 1);
	const char *name = lua_tostring(state, 2);
	float x = lua_tonumber(state, 3);
	float y = lua_tonumber(state, 4);
	float z = lua_tonumber(state, 5);
	float heading = lua_tonumber(state, 6);
	int color1 = lua_tointeger(state, 7);
	int color2 = lua_tointeger(state, 8);
	bool respawn = lua_toboolean(state, 9);
	int respawndelay = lua_tointeger(state, 10);

	int vehicleid = vehiclesPool.AddToVehiclePool();
	RakNet::RakString vehiclename = name;

	RakNet::BitStream sCreateVehicle;
	sCreateVehicle.Write(vehicleid);
	sCreateVehicle.Write(vehiclename);
	sCreateVehicle.Write(x);
	sCreateVehicle.Write(y);
	sCreateVehicle.Write(z);
	sCreateVehicle.Write(heading);
	sCreateVehicle.Write(color1);
	sCreateVehicle.Write(color2);
	sCreateVehicle.Write(respawn);
	sCreateVehicle.Write(respawndelay);
	NetworkManager->rpc.Signal("CreateVehicle", &sCreateVehicle, HIGH_PRIORITY, RELIABLE_ORDERED, 0, netPool.GetPlayerGUIDfromId(playerid), false, false);
	
	return 0;
}
