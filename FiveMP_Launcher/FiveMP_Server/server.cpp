#include "stdafx.h"

void sv_KickPlayer(int playerid)
{
	NetworkManager->server->CloseConnection(playerData[playerid].playerguid, true, 0);
}

void sv_PlayerConnect(RakNet::BitStream *bitStream, RakNet::Packet *packet) {
	int tempplayer;
	bitStream->Read(tempplayer);

	playerData[tempplayer].isConnected = true;

	PlayerManager->UpdatePlayerNickMaxDistance(tempplayer); //Just makes sure that client variable is in sync with server.
	VehicleManager->SpawnVehicles(tempplayer);

	OnPlayerConnect(sLUA, tempplayer);

	for (int i = 0; i < 100; i++) {
		if (playerData[i].isDefaultBlipRemoved) {

			RakNet::BitStream sRemoveDefaultBlipForPlayer;
			sRemoveDefaultBlipForPlayer.Write(i);
			NetworkManager->rpc.Signal("RemoveDefaultBlipForPlayer", &sRemoveDefaultBlipForPlayer, HIGH_PRIORITY, RELIABLE_ORDERED, 0, netPool.GetPlayerGUIDfromId(tempplayer), false, false);

		}
	}
};
