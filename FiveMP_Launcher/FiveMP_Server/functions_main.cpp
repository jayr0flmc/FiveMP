#include "stdafx.h"

int SetPlayerName(lua_State* state)
{
	int args = lua_gettop(state);

	printf("SetPlayerUsername() was called with %d arguments:\n", args);

	int playerid = lua_tointeger(state, 1);
	if (playerData[playerid].isConnected) {
		const char *string = lua_tostring(state, 2);

		playerData[playerid].playerusername = std::string(string);
	}
	return 0;
}

int GetPlayerName(lua_State* state)
{
	int args = lua_gettop(state);

	printf("GetPlayerUsername() was called with %d arguments:\n", args);

	int playerid = lua_tointeger(state, 1);
	if (playerData[playerid].isConnected) {
		lua_pushstring(state, playerData[playerid].playerusername.c_str());
	}
	else {
		lua_pushstring(state, "");
	}

	return 1;
}

int SetSpawnPoint(lua_State* state) {

	int args = lua_gettop(state);

	printf("SetSpawnPoint() was called with %d arguments.\n", args);

	float x = lua_tonumber(state, 1);
	float y = lua_tonumber(state, 2);
	float z = lua_tonumber(state, 3);

	int spawnid = spawnsPool.AddToSpawnPool(x, y, z);

	lua_pushinteger(state, spawnid);

	return 1;
}

int RemoveSpawnPoint(lua_State* state) {

	int args = lua_gettop(state);

	printf("RemoveSpawnPoint() was called with %d arguments.\n", args);

	int spawnid = lua_tonumber(state, 1);

	spawnsPool.RemoveFromSpawnPool(spawnid);

	return 0;
}

int IsPlayerConnected(lua_State * state)
{
	int args = lua_gettop(state);

	printf("IsPlayerConnected() was called with %d arguments\n", args);

	int playerid = lua_tointeger(state, 1);

	lua_pushboolean(state, playerData[playerid].isConnected);

	return 1;
}

int GetPlayerId(lua_State * state)
{
	int args = lua_gettop(state);

	printf("GetPlayerId() was called with %d arguments\n", args);

	const char *playername = lua_tostring(state, 1);

	RakNet::RakNetGUID tempgui = netPool.GetPlayerGUID((char *) playername);
	int tempid = netPool.GetPlayerID(tempgui);

	lua_pushinteger(state, tempid);

	return 1;
}