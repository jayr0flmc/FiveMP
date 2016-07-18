#include "stdafx.h"

int OnGameModeInit(lua_State* state)
{
	int result;

	printf("OnGameModeInit() was called\n");

	lua_getglobal(state, "OnGameModeInit");

	lua_pcall(state, 0, 0, 0);

	result = (int)lua_tointeger(state, -1);
	lua_pop(state, 1);

	return result;
}

int OnGameModeExit(lua_State * state)
{
	int result;

	printf("OnGameModeExit() was called\n");

	lua_getglobal(state, "OnGameModeExit");

	lua_pcall(state, 0, 0, 0);

	result = (int)lua_tointeger(state, -1);
	lua_pop(state, 1);

	return result;
}

int OnPlayerConnect(lua_State * state, int playerid)
{
	int result;

	printf("OnPlayerConnect() was called with %d\n", playerid);

	lua_getglobal(state, "OnPlayerConnect");

	lua_pushinteger(state, playerid);
	
	lua_pcall(state, 1, 1, 0);

	result = lua_tointeger(state, -1);
	lua_pop(state, 1);

	return result;
}

int OnPlayerDisconnect(lua_State * state, int playerid)
{
	int result;

	printf("OnPlayerDisconnect() was called with %d\n", playerid);

	lua_getglobal(state, "OnPlayerDisconnect"); // <---Change it on main.lua

	lua_pushinteger(state, playerid);

	lua_pcall(state, 1, 0, 0);

	result = lua_tointeger(state, -1);
	lua_pop(state, 1);

	return result;
}

int OnPlayerSpawn(lua_State * state, int playerid)
{
	int result;

	printf("OnPlayerSpawn() was called with %d\n", playerid);

	lua_getglobal(state, "OnPlayerSpawn");

	lua_pushinteger(state, playerid);

	lua_pcall(state, 1, 0, 0);

	result = (int)lua_tointeger(state, -1);
	lua_pop(state, 1);

	return result;
}

int OnPlayerDeath(lua_State * state, int playerid)
{
	int result;

	printf("OnPlayerDeath() was called with %d\n", playerid);

	lua_getglobal(state, "OnPlayerDeath");

	lua_pushinteger(state, playerid);

	lua_pcall(state, 1, 0, 0);

	result = (int)lua_tointeger(state, -1);
	lua_pop(state, 1);

	return result;
}

int OnPlayerUpdate(lua_State * state, int playerid)
{
	int result;

	//printf("OnPlayerUpdate() was called with %d\n", playerid); <--- Really spams

	lua_getglobal(state, "OnPlayerUpdate");

	lua_pushinteger(state, playerid);
	
	lua_pcall(state, 1, 1, 0);

	result = (int)lua_tointeger(state, -1);
	lua_pop(state, 1);

	return result;
}

int OnPlayerMessage(lua_State * state, int playerid, char* message)
{
	int result;
	
	lua_getglobal(state, "OnPlayerMessage");
	
	lua_pushinteger(state, playerid);
	lua_pushstring(state, message);
	
	lua_pcall(state, 2, 0, 0);
	
	result = (int)lua_tointeger(state, -1);
	lua_pop(state, 1);
	
	return result;
}