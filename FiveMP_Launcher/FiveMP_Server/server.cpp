#include "stdafx.h"

void sv_KickPlayer(int playerid)
{
	NetworkManager->server->CloseConnection(playerData[playerid].playerguid, true, 0);
}

void sv_PlayerConnect(RakNet::BitStream *bitStream, RakNet::Packet *packet) {
	int tempplayer;
	bitStream->Read(tempplayer);

	OnPlayerConnect(sLUA, tempplayer);
};
