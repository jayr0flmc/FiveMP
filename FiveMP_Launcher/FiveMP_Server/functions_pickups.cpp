#include "stdafx.h"

int CreatePickup(lua_State* state)
{
	int args = lua_gettop(state);

	printf("CreatePickup() was called with %d arguments.\n", args);

	int pickupid = -1;
	for (int i = 0; i < 100; i++) {
		if (!pickupData[i].used) {
			pickupid = i;
			pickupData[i].used = true;
			break;
		}
	}
	if (pickupid == -1) {
		std::cout << "Pickup limit was exceeded!" << std::endl;
		lua_pushinteger(state, -1);
	}
	else {
		lua_pushinteger(state, pickupid);
	}


	return 1;
}

int RemovePickup(lua_State * state)
{
	int args = lua_gettop(state);

	printf("RemovePickup() was called with %d arguments.\n", args);

	int pickupid = lua_tointeger(state, 1);

	if (pickupData[pickupid].used) {
		pickupData[pickupid].autoSync = false;
		pickupData[pickupid].pickupid = 0;
		pickupData[pickupid].x = 0.0f;
		pickupData[pickupid].y = 0.0f;
		pickupData[pickupid].z = 0.0f;
		pickupData[pickupid].used = false;
	}

	return 0;
}

int SetPickupPos(lua_State * state)
{
	int args = lua_gettop(state);

	printf("SetPickupPos() was called with %d arguments.\n", args);

	int pickupid = lua_tointeger(state, 1);
	if (pickupData[pickupid].used) {
		pickupData[pickupid].x = lua_tonumber(state, 2);
		pickupData[pickupid].y = lua_tonumber(state, 3);
		pickupData[pickupid].z = lua_tonumber(state, 4);
	}

	return 0;
}

int SetPickupModelID(lua_State * state)
{
	int args = lua_gettop(state);

	printf("SetPickupPos() was called with %d arguments.\n", args);

	int pickupid = lua_tointeger(state, 1);
	if (pickupData[pickupid].used) {
		pickupData[pickupid].pickupid = lua_tointeger(state, 2);
	}
	return 0;
}

int ShowPickupForPlayer(lua_State * state)
{
	int args = lua_gettop(state);

	printf("ShowPickupForPlayer() was called with %d arguments.\n", args);

	int pickupid = lua_tointeger(state, 1);
	int playerid = lua_tointeger(state, 2);
	if (pickupData[pickupid].used && playerData[playerid].isConnected) {

		RakNet::BitStream sShowPickupForPlayer;
		sShowPickupForPlayer.Write(pickupid);
		sShowPickupForPlayer.Write(pickupData[pickupid].pickupid);
		sShowPickupForPlayer.Write(pickupData[pickupid].x);
		sShowPickupForPlayer.Write(pickupData[pickupid].y);
		sShowPickupForPlayer.Write(pickupData[pickupid].z);
		NetworkManager->rpc.Signal("ShowPickupForPlayer", &sShowPickupForPlayer, HIGH_PRIORITY, RELIABLE_SEQUENCED, 0, netPool.GetPlayerGUIDfromId(playerid), false, false);

	}
	return 0;
}

int HidePickupForPlayer(lua_State * state)
{
	int args = lua_gettop(state);

	printf("ShowPickupForPlayer() was called with %d arguments.\n", args);

	int pickupid = lua_tointeger(state, 1);
	int playerid = lua_tointeger(state, 2);
	if (pickupData[pickupid].used && playerData[playerid].isConnected) {

		RakNet::BitStream sShowPickupForPlayer;
		sShowPickupForPlayer.Write(pickupid);
		NetworkManager->rpc.Signal("HidePickupForPlayer", &sShowPickupForPlayer, HIGH_PRIORITY, RELIABLE_SEQUENCED, 0, netPool.GetPlayerGUIDfromId(playerid), false, false);

	}
	return 0;
}
