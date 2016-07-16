#pragma once

int CreateBlip(lua_State* state);
int SetBlipLocationType(lua_State* state);
int ShowBlipForPlayer(lua_State* state);
int HideBlipForPlayer(lua_State* state);
int RemoveBlip(lua_State* state);
int SetBlipColor(lua_State* state);
int SetBlipImage(lua_State* state);
int SetBlipName(lua_State* state);

//Default blips that are created on player
int RemoveDefaultBlipFromPlayer(lua_State* state);
int IsDefaultBlipRemovedFromPlayer(lua_State* state);