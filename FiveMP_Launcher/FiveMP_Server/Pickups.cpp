#include "stdafx.h"

void RemovePickup(int pickup)
{
	if (pickupData[pickup].used) {
		RakNet::BitStream sShowPickupForPlayer;
		sShowPickupForPlayer.Write(pickup);

		for each(playerPool* player in pickupData[pickup].players) {
			NetworkManager->rpc.Signal("HidePickupForPlayer", &sShowPickupForPlayer, HIGH_PRIORITY, RELIABLE_SEQUENCED, 0, netPool.GetPlayerGUID((char*)player->playerusername.c_str()), false, false);
		}

		pickupData[pickup].autoSync = false;
		pickupData[pickup].model = "";
		pickupData[pickup].players.clear();
		pickupData[pickup].used = false;
		pickupData[pickup].x = 0.0f;
		pickupData[pickup].y = 0.0f;
		pickupData[pickup].z = 0.0f;
		pickupData[pickup].interval = 500;
	}

}
