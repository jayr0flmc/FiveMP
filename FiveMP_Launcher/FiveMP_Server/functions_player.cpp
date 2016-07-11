#include "stdafx.h"

int GivePlayerWeapon(lua_State* state)
{
	int args = lua_gettop(state);

	printf("GivePlayerWeapon() was called with %d arguments:\n", args);

	int playerid = lua_tointeger(state, 1);
	const char *string = lua_tostring(state, 2);
	int ammo = lua_tointeger(state, 3);

	RakNet::RakString weaponid = string;

	RakNet::BitStream sGivePlayerWeapon;
	sGivePlayerWeapon.Write(playerid); //Probably do not need to send this
	sGivePlayerWeapon.Write(weaponid);
	sGivePlayerWeapon.Write(ammo);
	rpc.Signal("GivePlayerWeapon", &sGivePlayerWeapon, HIGH_PRIORITY, RELIABLE_SEQUENCED, 0, netPool.GetPlayerGUIDfromId(playerid), false, false);

	lua_pushnumber(state, 124);
	return 1;
}

int RemovePlayerWeapon(lua_State* state)
{
	int args = lua_gettop(state);

	printf("RemovePlayerWeapon() was called with %d arguments:\n", args);

	int playerid = lua_tointeger(state, 1);
	const char *string = lua_tostring(state, 2);

	RakNet::RakString weaponid = string;

	RakNet::BitStream sRemovePlayerWeapon;
	sRemovePlayerWeapon.Write(playerid);
	sRemovePlayerWeapon.Write(weaponid);
	rpc.Signal("RemovePlayerWeapon", &sRemovePlayerWeapon, HIGH_PRIORITY, RELIABLE_SEQUENCED, 0, netPool.GetPlayerGUIDfromId(playerid), false, false);

	//lua_pushnumber(state, 124); //IS THIS EVEN NEEDED?
	return 1;
}

int GivePlayerAmmo(lua_State* state)
{
	int args = lua_gettop(state);

	printf("GivePlayerAmmo() was called with %d arguments:\n", args);

	int playerid = lua_tointeger(state, 1);
	const char *string = lua_tostring(state, 2);
	int ammo = lua_tointeger(state, 3);

	RakNet::RakString weaponid = string;

	RakNet::BitStream sGivePlayerAmmo;
	sGivePlayerAmmo.Write(playerid);
	sGivePlayerAmmo.Write(weaponid);
	sGivePlayerAmmo.Write(ammo);
	rpc.Signal("GivePlayerAmmo", &sGivePlayerAmmo, HIGH_PRIORITY, RELIABLE_SEQUENCED, 0, netPool.GetPlayerGUIDfromId(playerid), false, false);

	return 1;
}

int RemovePlayerAmmo(lua_State* state)
{
	int args = lua_gettop(state);

	printf("RemovePlayerAmmo() was called with %d arguments:\n", args);

	int playerid = lua_tointeger(state, 1);
	const char *string = lua_tostring(state, 2);
	int ammo = lua_tointeger(state, 3);

	RakNet::RakString weaponid = string;

	RakNet::BitStream sRemovePlayerAmmo;
	sRemovePlayerAmmo.Write(playerid);
	sRemovePlayerAmmo.Write(weaponid);
	sRemovePlayerAmmo.Write(ammo);
	rpc.Signal("RemovePlayerAmmo", &sRemovePlayerAmmo, HIGH_PRIORITY, RELIABLE_SEQUENCED, 0, netPool.GetPlayerGUIDfromId(playerid), false, false);

	return 1;
}

int SetPlayerMoney(lua_State * state)
{
	int args = lua_gettop(state);

	printf("SetPlayerMoney() was called with %d arguments.\n", args);

	int playerid = lua_tointeger(state, 1);
	playerData[playerid].money = lua_tointeger(state, 2);

	RakNet::BitStream sSetPlayerMoney;
	sSetPlayerMoney.Write(playerid);
	sSetPlayerMoney.Write(playerData[playerid].money);
	rpc.Signal("SetPlayerMoney", &sSetPlayerMoney, HIGH_PRIORITY, RELIABLE_SEQUENCED, 0, netPool.GetPlayerGUIDfromId(playerid), false, false);

	return 1;
}

int GivePlayerMoney(lua_State * state)
{
	int args = lua_gettop(state);

	printf("GivePlayerMoney() was called with %d arguments.\n", args);

	int playerid = lua_tointeger(state, 1);
	playerData[playerid].money += lua_tointeger(state, 2);

	RakNet::BitStream sSetPlayerMoney;
	sSetPlayerMoney.Write(playerid);
	sSetPlayerMoney.Write(playerData[playerid].money);
	rpc.Signal("SetPlayerMoney", &sSetPlayerMoney, HIGH_PRIORITY, RELIABLE_SEQUENCED, 0, netPool.GetPlayerGUIDfromId(playerid), false, false);

	return 1;
}

int GetPlayerMoney(lua_State * state)
{
	int args = lua_gettop(state);

	printf("GetPlayerMoney() was called with %d arguments.\n", args);

	int playerid = lua_tointeger(state, 1);

	std::cout << "GetPlayerMoney value: " << playerData[playerid].money << std::endl; // This prints good number, but inside lua i get nil value.
	
	lua_pushnumber(state, playerData[playerid].money);

	return 1;
}

int KickPlayer(lua_State * state) {

	int args = lua_gettop(state);

	printf("KickPlayer() was called with %d arguments.\n", args);

	int playerid = lua_tointeger(state, 1);
	RakNet::RakString reason = lua_tostring(state, 2);

	//I leave rest to Dev

	return 1;
}
