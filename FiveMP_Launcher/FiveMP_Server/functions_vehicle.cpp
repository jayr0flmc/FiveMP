#include "stdafx.h"

int CreateVehicle(lua_State* state)
{
	int args = lua_gettop(state);

	printf("CreateVehicle() was called with %d arguments:\n", args);

	const char *name = lua_tostring(state, 1);
	float x = lua_tonumber(state, 2);
	float y = lua_tonumber(state, 3);
	float z = lua_tonumber(state, 4);
	float heading = lua_tonumber(state, 5);
	int color1 = lua_tointeger(state, 6);
	int color2 = lua_tointeger(state, 7);
	bool respawn = lua_toboolean(state, 8);
	int respawndelay = lua_tointeger(state, 9);

	int vehicleid = vehiclesPool.AddToVehiclePool(name, x, y, z, heading, color1, color2, respawn, respawndelay);

	lua_pushinteger(state, vehicleid);


	RakNet::RakString vehiclename = vehicleData[vehicleid].spawnvehicleModel;

	RakNet::BitStream sCreateVehicle;
	sCreateVehicle.Write(vehicleData[vehicleid].vehicleid);
	sCreateVehicle.Write(vehiclename);
	sCreateVehicle.Write(vehicleData[vehicleid].x);
	sCreateVehicle.Write(vehicleData[vehicleid].y);
	sCreateVehicle.Write(vehicleData[vehicleid].z);
	sCreateVehicle.Write(vehicleData[vehicleid].r);
	sCreateVehicle.Write(vehicleData[vehicleid].vehicleColor1);
	sCreateVehicle.Write(vehicleData[vehicleid].vehicleColor2);
	sCreateVehicle.Write(vehicleData[vehicleid].respawn);
	sCreateVehicle.Write(vehicleData[vehicleid].respawndelay);
	NetworkManager->rpc.Signal("CreateVehicle", &sCreateVehicle, HIGH_PRIORITY, RELIABLE_ORDERED, 0, RakNet::UNASSIGNED_SYSTEM_ADDRESS, true, false);

	return 1;
}

int RemoveVehicle(lua_State* state)
{
	int args = lua_gettop(state);

	printf("RemoveVehicle() was called with %d arguments:\n", args);

	int vehicleid = lua_tonumber(state, 1);

	vehiclesPool.RemoveFromVehiclePool(vehicleid);

	RakNet::BitStream sRemoveVehicle;
	sRemoveVehicle.Write(vehicleid);
	NetworkManager->rpc.Signal("RemoveVehicle", &sRemoveVehicle, HIGH_PRIORITY, RELIABLE_ORDERED, 0, RakNet::UNASSIGNED_SYSTEM_ADDRESS, true, false);

	return 0;
}

int SetVehicleColor(lua_State* state)
{
	int args = lua_gettop(state);

	printf("SetVehicleColor() was called with %d arguments:\n", args);

	int vehicleid = lua_tonumber(state, 1);
	int color1 = lua_tonumber(state, 2);
	int color2 = lua_tonumber(state, 3);

	vehicleData[vehicleid].vehicleColor1 = color1;
	vehicleData[vehicleid].vehicleColor2 = color2;

	RakNet::BitStream sVehicleColor;
	sVehicleColor.Write(vehicleid);
	sVehicleColor.Write(color1);
	sVehicleColor.Write(color2);
	NetworkManager->rpc.Signal("SetVehicleColor", &sVehicleColor, HIGH_PRIORITY, RELIABLE_ORDERED, 0, RakNet::UNASSIGNED_SYSTEM_ADDRESS, true, false);

	return 0;
}

int SetVehicleCustomColor(lua_State* state)
{
	int args = lua_gettop(state);

	printf("SetVehicleCustomColor() was called with %d arguments:\n", args);

	int vehicleid = lua_tonumber(state, 1);
	int layer = lua_tonumber(state, 2);
	int r = lua_tonumber(state, 3);
	int g = lua_tonumber(state, 4);
	int b = lua_tonumber(state, 5);

	if (layer == 1) {
		vehicleData[vehicleid].primarycolor.set(r, g, b);
	}
	else if (layer == 2) {
		vehicleData[vehicleid].secondarycolor.set(r, g, b);
	}
	else {
		printf("SetVehicleCustomColor() 'layer' argument incorectly used, must be 1 or 2");
	}

	RakNet::BitStream sVehicleColor;
	sVehicleColor.Write(vehicleid);
	sVehicleColor.Write(layer);
	sVehicleColor.Write(r);
	sVehicleColor.Write(g);
	sVehicleColor.Write(b);
	NetworkManager->rpc.Signal("SetVehicleCustomColor", &sVehicleColor, HIGH_PRIORITY, RELIABLE_ORDERED, 0, RakNet::UNASSIGNED_SYSTEM_ADDRESS, true, false);

	return 0;
}
