#pragma once

int SetPlayerName(lua_State* state);
int GetPlayerName(lua_State* state);
int GetPlayerId(lua_State* state);

int SetSpawnPoint(lua_State* state);
int RemoveSpawnPoint(lua_State* state);

int IsPlayerConnected(lua_State* state);