#include "stdafx.h"

int ShowMessageToPlayer(lua_State* state)
{
	int args = lua_gettop(state);

	printf("ShowMessageToPlayer() was called with %d arguments:\n", args);

	int playerid		= lua_tointeger(state, 1);
	const char *string	= lua_tostring(state, 2);

	RakNet::RakString textstring = string;

	RakNet::BitStream sShowMessageToPlayer;
	sShowMessageToPlayer.Write(textstring);
	NetworkManager->rpc.Signal("ShowMessageToPlayer", &sShowMessageToPlayer, HIGH_PRIORITY, RELIABLE_SEQUENCED, 0, netPool.GetPlayerGUIDfromId(playerid), false, false);

	return 0;
}

int ShowMessageToAll(lua_State* state)
{
	int args = lua_gettop(state);

	printf("ShowMessageToAll() was called with %d arguments:\n", args);

	const char *string = lua_tostring(state, 1);

	RakNet::RakString textstring = string;

	RakNet::BitStream sShowMessageToPlayer;
	sShowMessageToPlayer.Write(textstring);
	NetworkManager->rpc.Signal("ShowMessageToPlayer", &sShowMessageToPlayer, HIGH_PRIORITY, RELIABLE_SEQUENCED, 0, RakNet::UNASSIGNED_SYSTEM_ADDRESS, true, false);

	return 0;
}