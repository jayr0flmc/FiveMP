#pragma once

int CreatePickup(lua_State* state);
int RemovePickup(lua_State* state);
int SetPickupPos(lua_State* state);
int SetPickupModelID(lua_State* state);
int ShowPickupForPlayer(lua_State* state);
int HidePickupForPlayer(lua_State* state);
int SetPickupRespawnTime(lua_State* state);
