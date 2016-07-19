#include "stdafx.h"
#include "server.h"

#pragma region "Weapons"

int GivePlayerWeapon(lua_State* state)
{
	int args = lua_gettop(state);

	printf("GivePlayerWeapon() was called with %d arguments:\n", args);

	int playerid = lua_tointeger(state, 1);
	if (playerData[playerid].isConnected) {
		const char *string = lua_tostring(state, 2);
		int ammo = lua_tointeger(state, 3);

		RakNet::RakString weaponid = string;

		RakNet::BitStream sGivePlayerWeapon;
		sGivePlayerWeapon.Write(playerid); //Probably do not need to send this
		sGivePlayerWeapon.Write(weaponid);
		sGivePlayerWeapon.Write(ammo);
		NetworkManager->rpc.Signal("GivePlayerWeapon", &sGivePlayerWeapon, HIGH_PRIORITY, RELIABLE_SEQUENCED, 0, netPool.GetPlayerGUIDfromId(playerid), false, false);
	}

	return 0;
}

int RemovePlayerWeapon(lua_State* state)
{
	int args = lua_gettop(state);

	printf("RemovePlayerWeapon() was called with %d arguments:\n", args);

	int playerid = lua_tointeger(state, 1);
	if (playerData[playerid].isConnected) {
		const char *string = lua_tostring(state, 2);

		RakNet::RakString weaponid = string;

		RakNet::BitStream sRemovePlayerWeapon;
		sRemovePlayerWeapon.Write(playerid);
		sRemovePlayerWeapon.Write(weaponid);
		NetworkManager->rpc.Signal("RemovePlayerWeapon", &sRemovePlayerWeapon, HIGH_PRIORITY, RELIABLE_SEQUENCED, 0, netPool.GetPlayerGUIDfromId(playerid), false, false);
	}

	return 0;
}

int GivePlayerAmmo(lua_State* state)
{
	int args = lua_gettop(state);

	printf("GivePlayerAmmo() was called with %d arguments:\n", args);

	int playerid = lua_tointeger(state, 1);
	if (playerData[playerid].isConnected) {
		const char *string = lua_tostring(state, 2);
		int ammo = lua_tointeger(state, 3);

		RakNet::RakString weaponid = string;

		RakNet::BitStream sGivePlayerAmmo;
		sGivePlayerAmmo.Write(playerid);
		sGivePlayerAmmo.Write(weaponid);
		sGivePlayerAmmo.Write(ammo);
		NetworkManager->rpc.Signal("GivePlayerAmmo", &sGivePlayerAmmo, HIGH_PRIORITY, RELIABLE_SEQUENCED, 0, netPool.GetPlayerGUIDfromId(playerid), false, false);
	}

	return 0;
}

int RemovePlayerAmmo(lua_State* state)
{
	int args = lua_gettop(state);

	printf("RemovePlayerAmmo() was called with %d arguments:\n", args);

	int playerid = lua_tointeger(state, 1);
	if (playerData[playerid].isConnected) {
		const char *string = lua_tostring(state, 2);
		int ammo = lua_tointeger(state, 3);

		RakNet::RakString weaponid = string;

		RakNet::BitStream sRemovePlayerAmmo;
		sRemovePlayerAmmo.Write(playerid);
		sRemovePlayerAmmo.Write(weaponid);
		sRemovePlayerAmmo.Write(ammo);
		NetworkManager->rpc.Signal("RemovePlayerAmmo", &sRemovePlayerAmmo, HIGH_PRIORITY, RELIABLE_SEQUENCED, 0, netPool.GetPlayerGUIDfromId(playerid), false, false);
	}

	return 0;
}

int RemovePlayerWeapons(lua_State* state)
{
	int args = lua_gettop(state);

	printf("RemovePlayerWeapons() was called with %d arguments:\n", args);

	int playerid = lua_tointeger(state, 1);
	if (playerData[playerid].isConnected) {

		RakNet::BitStream sRemovePlayerWeapons;
		sRemovePlayerWeapons.Write(playerid);
		NetworkManager->rpc.Signal("RemovePlayerWeapons", &sRemovePlayerWeapons, HIGH_PRIORITY, RELIABLE_SEQUENCED, 0, netPool.GetPlayerGUIDfromId(playerid), false, false);
	}

	return 0;
}

#pragma endregion 
#pragma region "Money"

int SetPlayerMoney(lua_State * state)
{
	int args = lua_gettop(state);

	printf("SetPlayerMoney() was called with %d arguments.\n", args);

	int playerid = lua_tointeger(state, 1);
	if (playerData[playerid].isConnected) {
		playerData[playerid].money = lua_tointeger(state, 2);

		RakNet::BitStream sSetPlayerMoney;
		sSetPlayerMoney.Write(playerid);
		sSetPlayerMoney.Write(playerData[playerid].money);
		NetworkManager->rpc.Signal("SetPlayerMoney", &sSetPlayerMoney, HIGH_PRIORITY, RELIABLE_SEQUENCED, 0, netPool.GetPlayerGUIDfromId(playerid), false, false);
	}
	return 0;
}

int GivePlayerMoney(lua_State * state)
{
	int args = lua_gettop(state);

	printf("GivePlayerMoney() was called with %d arguments.\n", args);

	int playerid = lua_tointeger(state, 1);
	if (playerData[playerid].isConnected) {
		playerData[playerid].money += lua_tointeger(state, 2);

		RakNet::BitStream sSetPlayerMoney;
		sSetPlayerMoney.Write(playerid);
		sSetPlayerMoney.Write(playerData[playerid].money);
		NetworkManager->rpc.Signal("SetPlayerMoney", &sSetPlayerMoney, HIGH_PRIORITY, RELIABLE_SEQUENCED, 0, netPool.GetPlayerGUIDfromId(playerid), false, false);
	}
	return 0;
}

int GetPlayerMoney(lua_State * state)
{
	int args = lua_gettop(state);

	printf("GetPlayerMoney() was called with %d arguments.\n", args);

	int playerid = lua_tointeger(state, 1);
	if (playerData[playerid].isConnected) {
		lua_pushinteger(state, playerData[playerid].money);
	}
	else {
		lua_pushinteger(state, 0);
	}
	return 1;
}

#pragma endregion 
#pragma region "Network"

int KickPlayer(lua_State * state) {

	int args = lua_gettop(state);

	printf("KickPlayer() was called with %d arguments.\n", args);

	int playerid = lua_tointeger(state, 1);
	if (playerData[playerid].isConnected) {
		RakNet::RakString reason = lua_tostring(state, 2);

		//I tried to finish it but if it's bad feel free to delete it.

		RakNet::RakString message = "You were kicked out of the server. Reason: ~b~" + reason;

		//Show kick message
		RakNet::BitStream sKickPlayer;
		sKickPlayer.Write(playerid);
		sKickPlayer.Write(message);
		NetworkManager->rpc.Signal("ShowMessageToPlayer", &sKickPlayer, HIGH_PRIORITY, RELIABLE_SEQUENCED, 0, netPool.GetPlayerGUIDfromId(playerid), false, false);

		//Disconect player from the server
		RakSleep(100); //Sleep a bit that message would get sent
		sv_KickPlayer(playerid); //If you dont like it its in server.h
	}
	return 0;
}

#pragma endregion 
#pragma region "Player Position/Head/Angles"

int SetPlayerPos(lua_State* state) {

	int args = lua_gettop(state);

	printf("SetPlayerPos() was called with %d arguments.\n", args);

	int playerid = lua_tointeger(state, 1);
	if (playerData[playerid].isConnected) {
		float posx = lua_tonumber(state, 2);
		float posy = lua_tonumber(state, 3);
		float posz = lua_tonumber(state, 4);

		//There's no need for that since transitioning works perfectly!
		//std::cout << posx << " | " << posy << " | " << posz << std::endl;

		playerData[playerid].x = posx;
		playerData[playerid].y = posy;
		playerData[playerid].z = posz;

		RakNet::BitStream sSetPlayerPos;
		sSetPlayerPos.Write(playerid);
		sSetPlayerPos.Write(posx);
		sSetPlayerPos.Write(posy);
		sSetPlayerPos.Write(posz);
		NetworkManager->rpc.Signal("SetPlayerPos", &sSetPlayerPos, HIGH_PRIORITY, RELIABLE_SEQUENCED, 0, netPool.GetPlayerGUIDfromId(playerid), false, false);
	}
	return 0;
}

int GetPlayerPos(lua_State* state) {

	int args = lua_gettop(state);

	printf("GetPlayerPos() was called with %d arguments.\n", args);

	int playerid = lua_tointeger(state, 1);
	if (playerData[playerid].isConnected) {
		lua_pushnumber(state, playerData[playerid].x);
		lua_pushnumber(state, playerData[playerid].y);
		lua_pushnumber(state, playerData[playerid].z);
	}
	else {
		lua_pushnumber(state, 0);
		lua_pushnumber(state, 0);
		lua_pushnumber(state, 0);
	}
	return 3;
}

int SetPlayerFacingAngle(lua_State* state) {

	int args = lua_gettop(state);

	printf("SetPlayerFacingAngle() was called with %d arguments.\n", args);

	int playerid = lua_tointeger(state, 1);
	if (playerData[playerid].isConnected) {
		float rotation = 360 - lua_tonumber(state, 2);

		playerData[playerid].r = rotation;

		RakNet::BitStream sSetPlayerFacingAngle;
		sSetPlayerFacingAngle.Write(playerid);
		sSetPlayerFacingAngle.Write(rotation);
		NetworkManager->rpc.Signal("SetPlayerFacingAngle", &sSetPlayerFacingAngle, HIGH_PRIORITY, RELIABLE_SEQUENCED, 0, netPool.GetPlayerGUIDfromId(playerid), false, false);
	}
	return 0;
}

int GetPlayerFacingAngle(lua_State * state)
{
	int args = lua_gettop(state);

	printf("GetPlayerFacingAngle() was called with %d arguments.\n", args);

	int playerid = lua_tointeger(state, 1);
	if (playerData[playerid].isConnected) {
		lua_pushnumber(state, 360 - playerData[playerid].r);
	}
	else {
		lua_pushnumber(state, 0.0f);
	}
	
	return 1;
}

#pragma endregion 
#pragma region "Player Score"

int SetPlayerScore(lua_State* state) {
	
	int args = lua_gettop(state);

	printf("SetPlayerScore() was called with %d arguments.\n", args);

	int playerid = lua_tointeger(state, 1);
	if (playerData[playerid].isConnected) {
		playerData[playerid].score = lua_tointeger(state, 2);
	}
	return 0;
}

int GivePlayerScore(lua_State* state) {

	int args = lua_gettop(state);

	printf("GivePlayerScore() was called with %d arguments.\n", args);

	int playerid = lua_tointeger(state, 1);
	if (playerData[playerid].isConnected) {
		playerData[playerid].score += lua_tointeger(state, 2);
	}
	return 0;
}

int GetPlayerScore(lua_State* state) {

	int args = lua_gettop(state);

	printf("GetPlayerScore() was called with %d arguments.\n", args);

	int playerid = lua_tointeger(state, 1);
	if (playerData[playerid].isConnected) {
		lua_pushinteger(state, playerData[playerid].score);
	}
	else {
		lua_pushinteger(state, 0);
	}
	
	return 1;
}

#pragma endregion 
#pragma region "Player Health and Armour"

int SetPlayerHealth(lua_State* state) {
	
	int args = lua_gettop(state);

	printf("SetPlayerHealth() was called with %d arguments.\n", args);

	int playerid = lua_tointeger(state, 1);
	if (playerData[playerid].isConnected) {
		playerData[playerid].pedHealth = lua_tointeger(state, 2);

		RakNet::BitStream sSetPlayerHealth;
		sSetPlayerHealth.Write(playerid);
		sSetPlayerHealth.Write(playerData[playerid].pedHealth);
		NetworkManager->rpc.Signal("SetPlayerHealth", &sSetPlayerHealth, HIGH_PRIORITY, RELIABLE_SEQUENCED, 0, netPool.GetPlayerGUIDfromId(playerid), false, false);
	}
	return 0;
}

int GetPlayerHealth(lua_State* state) {

	int args = lua_gettop(state);

	printf("GetPlayerHealth() was called with %d arguments.\n", args);

	int playerid = lua_tointeger(state, 1);

	if (playerData[playerid].isConnected) {
		lua_pushinteger(state, playerData[playerid].pedHealth);
	}
	else {
		lua_pushinteger(state, 0);
	}
	
	return 1;
}

int SetPlayerArmour(lua_State* state) {

	int args = lua_gettop(state);

	printf("SetPlayerArmour() was called with %d arguments.\n", args);

	int playerid = lua_tointeger(state, 1);
	if (playerData[playerid].isConnected) {
		playerData[playerid].pedArmour = lua_tointeger(state, 2);

		RakNet::BitStream sSetPlayerArmour;
		sSetPlayerArmour.Write(playerid);
		sSetPlayerArmour.Write(playerData[playerid].pedArmour);
		NetworkManager->rpc.Signal("SetPlayerArmour", &sSetPlayerArmour, HIGH_PRIORITY, RELIABLE_SEQUENCED, 0, netPool.GetPlayerGUIDfromId(playerid), false, false);
	}
	return 0;
}

int GetPlayerArmour(lua_State* state) {

	int args = lua_gettop(state);

	printf("GetPlayerArmour() was called with %d arguments.\n", args);

	int playerid = lua_tointeger(state, 1);
	if (playerData[playerid].isConnected) {
		lua_pushinteger(state, playerData[playerid].pedArmour);
	}
	else {
		lua_pushinteger(state, 0);
	}
	
	return 1;
}

#pragma endregion 
#pragma region "Time"

int SetTime(lua_State* state) {

	int args = lua_gettop(state);

	printf("SetTime() was called with %d arguments.\n", args);

	Config->ServerTimeHour = lua_tointeger(state, 1);
	Config->ServerTimeMinute = lua_tointeger(state, 2);

	return 0;
}

int GetTime(lua_State* state) {

	int args = lua_gettop(state);

	printf("GetTime() was called with %d arguments.\n", args);

	lua_pushinteger(state, Config->ServerTimeHour);
	lua_pushinteger(state, Config->ServerTimeMinute);

	return 2;
}

#pragma endregion 

int SetPlayerMaxNickDrawDistance(lua_State* state) {

	int args = lua_gettop(state);

	printf("SetPlayerMaxNickDrawDistance() was called with %d arguments.\n", args);

	int playerid = lua_tointeger(state, 1);
	if (playerData[playerid].isConnected) {
		playerData[playerid].maxNickDistance = lua_tonumber(state, 2);

		PlayerManager->UpdatePlayerNickMaxDistance(playerid);
	}
	return 0;
}

#pragma region "Player Model"

int SetPlayerModel(lua_State* state) {

	int args = lua_gettop(state);

	printf("SetPlayerModel() was called with %d arguments.\n", args);

	int playerid = lua_tointeger(state, 1);
	if (playerData[playerid].isConnected) {
		int modelid = lua_tointeger(state, 2);

		playerData[playerid].pedModel = modelid;

		RakNet::BitStream sSetPlayerModel;
		sSetPlayerModel.Write(playerid);
		sSetPlayerModel.Write(modelid);
		NetworkManager->rpc.Signal("SetPlayerModel", &sSetPlayerModel, HIGH_PRIORITY, RELIABLE_SEQUENCED, 0, netPool.GetPlayerGUIDfromId(playerid), false, false);
	}
	return 0;
}

int GetPlayerModel(lua_State * state)
{
	int args = lua_gettop(state);

	printf("GetPlayerModel() was called with %d arguments.\n", args);

	int playerid = lua_tointeger(state, 1);
	if (playerData[playerid].isConnected) {
		lua_pushinteger(state, playerData[playerid].pedModel);
	}
	else {
		lua_pushinteger(state, 0);
	}

	return 1;
}

int SetPedComponentVariation(lua_State* state) {
	int args = lua_gettop(state);

	printf("SetPedComponentVariation() was called with %d arguments.\n", args);

	int playerid = lua_tointeger(state, 1);
	if (playerData[playerid].isConnected) {
		int componentid = lua_tointeger(state, 2);
		int drawableid = lua_tointeger(state, 3);
		int textureid = lua_tointeger(state, 4);
		int paletteid = lua_tointeger(state, 5);

		RakNet::BitStream sSetPedComponentVariation;
		sSetPedComponentVariation.Write(playerid);
		sSetPedComponentVariation.Write(componentid);
		sSetPedComponentVariation.Write(drawableid);
		sSetPedComponentVariation.Write(textureid);
		sSetPedComponentVariation.Write(paletteid);
		NetworkManager->rpc.Signal("SetPedComponentVariation", &sSetPedComponentVariation, HIGH_PRIORITY, RELIABLE_SEQUENCED, 0, netPool.GetPlayerGUIDfromId(playerid), false, false);
	}

	return 0;
}

int SetPlayerControlable(lua_State * state)
{
	int args = lua_gettop(state);

	printf("SetPlayerControlable() was called with %d arguments.\n", args);

	int playerid = lua_tointeger(state, 1);
	if (playerData[playerid].isConnected) {
		bool value = lua_toboolean(state, 2);

		RakNet::BitStream sSetPlayerC;
		sSetPlayerC.Write(playerid);
		sSetPlayerC.Write(value);
		NetworkManager->rpc.Signal("SetPlayerControlable", &sSetPlayerC, HIGH_PRIORITY, RELIABLE_SEQUENCED, 0, netPool.GetPlayerGUIDfromId(playerid), false, false);
	}
	return 0;
}

#pragma endregion 
