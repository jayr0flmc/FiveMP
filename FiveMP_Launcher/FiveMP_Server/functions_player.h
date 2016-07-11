#pragma once

int GivePlayerWeapon(lua_State* state);
int RemovePlayerWeapon(lua_State* state);
int GivePlayerAmmo(lua_State* state);
int RemovePlayerAmmo(lua_State* state);
int SetPlayerMoney(lua_State* state);
int GivePlayerMoney(lua_State* state);
int GetPlayerMoney(lua_State* state);
int KickPlayer(lua_State* state);