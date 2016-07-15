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

	return 1;
}

int RemoveVehicle(lua_State* state)
{
	int args = lua_gettop(state);

	printf("RemoveVehicle() was called with %d arguments:\n", args);

	int vehicleid = lua_tonumber(state, 1);

	vehiclesPool.RemoveFromVehiclePool(vehicleid);

	return 0;
}

