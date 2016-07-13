#include "stdafx.h"

int SetPlayerUsername(lua_State* state)
{
	int args = lua_gettop(state);

	printf("SetPlayerUsername() was called with %d arguments:\n", args);

	int playerid = lua_tointeger(state, 1);
	const char *string = lua_tostring(state, 2);

	playerData[playerid].playerusername = (char*)string;

	return 0;
}

int GetPlayerUsername(lua_State* state)
{
	int args = lua_gettop(state);

	printf("GetPlayerUsername() was called with %d arguments:\n", args);

	int playerid = lua_tointeger(state, 1);

	lua_pushstring(state, playerData[playerid].playerusername);

	return 1;
}

int SetSpawnPoint(lua_State* state) {

	int args = lua_gettop(state);

	printf("SetSpawn() was called with %d arguments.\n", args);

	int spawnid = lua_tointeger(state, 1);
	spawnData[spawnid].spawnid = spawnid;
	spawnData[spawnid].x = lua_tonumber(state, 2);
	spawnData[spawnid].y = lua_tonumber(state, 3);
	spawnData[spawnid].z = lua_tonumber(state, 4);

	return 0;
}