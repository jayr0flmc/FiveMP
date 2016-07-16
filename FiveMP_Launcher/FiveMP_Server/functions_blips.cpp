#include "stdafx.h"

int CreateBlip(lua_State * state)
{
	int args = lua_gettop(state);

	printf("CreateBlip() was called with %d arguments.\n", args);

	bool fblip = false;

	for (int i = 0; i < 100; i++) {
		if (!blipData[i].used) {
			blipData[i].used = true;
			lua_pushinteger(state, i);
			return 1;
		}
	}

	lua_pushinteger(state, -1);
	return 1;
}

int SetBlipLocationType(lua_State * state)
{
	int args = lua_gettop(state);

	printf("SetBlipLocationType() was called with %d arguments.\n", args);

	int blipid = lua_tointeger(state, 1);
	if (blipData[blipid].used) {
		blipData[blipid].locationType = lua_tointeger(state, 2);
		switch (blipData[blipid].locationType) {
		case 0: { //location location type
			blipData[blipid].x = lua_tonumber(state, 3);
			blipData[blipid].y = lua_tonumber(state, 4);
			blipData[blipid].z = lua_tonumber(state, 5);
			break;
		}
		case 1: { //attached to vehicle type
			blipData[blipid].attachID = lua_tointeger(state, 3);
			break;
		}
		case 2: { //attached to player
			blipData[blipid].attachID = lua_tointeger(state, 3);
			break;
		}
		case 3: { //attached to pickup
			blipData[blipid].attachID = lua_tointeger(state, 3);
		}
		case 4: { //attached to racepoint.
			blipData[blipid].attachID = lua_tointeger(state, 3);
		}
		}
	}
	return 0;
}

int ShowBlipForPlayer(lua_State * state)
{
	int args = lua_gettop(state);

	printf("ShowBlipForPlayer() was called with %d arguments.\n", args);

	int blipid = lua_tointeger(state, 1);
	int playerid = lua_tointeger(state, 2);
	if (blipData[blipid].used && playerData[playerid].isConnected) {
		RakNet::BitStream sShowBlipForPlayer;
		sShowBlipForPlayer.Write(blipid);
		sShowBlipForPlayer.Write(blipData[blipid].locationType);
		sShowBlipForPlayer.Write(blipData[blipid].x);
		sShowBlipForPlayer.Write(blipData[blipid].y);
		sShowBlipForPlayer.Write(blipData[blipid].z);
		sShowBlipForPlayer.Write(blipData[blipid].attachID);
		sShowBlipForPlayer.Write(blipData[blipid].color);
		sShowBlipForPlayer.Write(blipData[blipid].spriteid);
		sShowBlipForPlayer.Write(blipData[blipid].name.c_str());
		NetworkManager->rpc.Signal("ShowBlipForPlayer", &sShowBlipForPlayer, HIGH_PRIORITY, RELIABLE_ORDERED, 0, netPool.GetPlayerGUIDfromId(playerid), false, false);
	}
	return 0;
}

int HideBlipForPlayer(lua_State * state)
{
	int args = lua_gettop(state);

	printf("HideBlipForPlayer() was called with %d arguments.\n", args);

	int blipid = lua_tointeger(state, 1);
	int playerid = lua_tointeger(state, 2);
	if (blipData[blipid].used && playerData[playerid].isConnected) {
		RakNet::BitStream sShowBlipForPlayer;
		sShowBlipForPlayer.Write(blipid);
		NetworkManager->rpc.Signal("HideBlipForPlayer", &sShowBlipForPlayer, HIGH_PRIORITY, RELIABLE_ORDERED, 0, netPool.GetPlayerGUIDfromId(playerid), false, false);
	}
	return 0;
}

int RemoveBlip(lua_State * state)
{
	int args = lua_gettop(state);

	printf("HideBlipForPlayer() was called with %d arguments.\n", args);

	int blipid = lua_tointeger(state, 1);

	blipData[blipid].locationType = 0;
	blipData[blipid].x = 0.0f;
	blipData[blipid].y = 0.0f;
	blipData[blipid].z = 0.0f;
	blipData[blipid].attachID = 0;
	blipData[blipid].color = 0;
	blipData[blipid].spriteid = 1;
	blipData[blipid].name = std::string("No name");
	blipData[blipid].used = false;

	return 0;
}

/*
Blip Colors:
0 - White
1 - Red
2 -

*/

int SetBlipColor(lua_State * state)
{
	int args = lua_gettop(state);

	printf("SetBlipColor() was called with %d arguments.\n", args);

	int blipid = lua_tointeger(state, 1);
	if (blipData[blipid].used) {
		int color = lua_tointeger(state, 2);
		blipData[blipid].color = color;
	}

	return 0;
}

int SetBlipImage(lua_State * state)
{
	int args = lua_gettop(state);

	printf("SetBlipImage() was called with %d arguments.\n", args);

	int blipid = lua_tointeger(state, 1);
	if (blipData[blipid].used) {
		blipData[blipid].spriteid = lua_tointeger(state, 2);
	}

	return 0;
}

int SetBlipName(lua_State * state)
{
	int args = lua_gettop(state);

	printf("SetBlipName() was called with %d arguments.\n", args);

	int blipid = lua_tointeger(state, 1);
	if (blipData[blipid].used) {
		blipData[blipid].name = std::string(lua_tostring(state, 2));
	}

	return 0;
}

int RemoveDefaultBlipFromPlayer(lua_State * state)
{
	int args = lua_gettop(state);

	printf("RemoveDefaultBlipFromPlayer() was called with %d arguments.\n", args);

	int playerid = lua_tointeger(state, 1);
	if (playerData[playerid].isConnected) {
		//We will send this with packets.
		playerData[playerid].isDefaultBlipRemoved = true;

		RakNet::BitStream sRemoveDefaultBlipForPlayer;
		sRemoveDefaultBlipForPlayer.Write(playerid);
		NetworkManager->rpc.Signal("RemoveDefaultBlipForPlayer", &sRemoveDefaultBlipForPlayer, HIGH_PRIORITY, RELIABLE_ORDERED, 0, RakNet::UNASSIGNED_SYSTEM_ADDRESS, true, false);
	}

	return 1;
}

int IsDefaultBlipRemovedFromPlayer(lua_State * state)
{
	int args = lua_gettop(state);

	printf("IsDefaultBlipRemovedFromPlayer() was called with %d arguments.\n", args);

	int playerid = lua_tointeger(state, 1);
	if (playerData[playerid].isConnected) {
		lua_pushboolean(state, playerData[playerid].isDefaultBlipRemoved);
	}
	else {
		lua_pushinteger(state, -1);
	}

	return 0;
}
