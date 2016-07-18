#pragma once

int OnGameModeInit(lua_State* state);
int OnGameModeExit(lua_State* state);

int OnPlayerConnect(lua_State * state, int playerid);
int OnPlayerDisconnect(lua_State * state, int playerid);

int OnPlayerSpawn(lua_State * state, int playerid);
int OnPlayerDeath(lua_State * state, int playerid);

int OnPlayerUpdate(lua_State* state, int playerid);
int OnPlayerMessage(lua_State * state, int playerid, char* message);
int OnPlayerCommand(lua_State * state, int playerid, char* message);
