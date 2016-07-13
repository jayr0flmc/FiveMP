#include "stdafx.h"

int SetPlayerName(lua_State* state)
{
	int args = lua_gettop(state);

	printf("SetPlayerUsername() was called with %d arguments:\n", args);

	int playerid = lua_tointeger(state, 1);
	const char *string = lua_tostring(state, 2);

	playerData[playerid].playerusername = std::string(string);

	return 0;
}

int GetPlayerName(lua_State* state)
{
	int args = lua_gettop(state);

	printf("GetPlayerUsername() was called with %d arguments:\n", args);

	int playerid = lua_tointeger(state, 1);

	lua_pushstring(state, playerData[playerid].playerusername.c_str());

	return 1;
}

int SetSpawnPoint(lua_State* state) {

	int args = lua_gettop(state);

	printf("SetSpawn() was called with %d arguments.\n", args);

	float x = lua_tonumber(state, 1);
	float y = lua_tonumber(state, 2);
	float z = lua_tonumber(state, 3);

	int spawnid = spawnsPool.AddToSpawnPool(x, y, z);

	lua_pushinteger(state, spawnid);

	return 1;
}