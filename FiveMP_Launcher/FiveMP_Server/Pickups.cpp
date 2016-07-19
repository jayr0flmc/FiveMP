#include "stdafx.h"

void RemovePickup(int pickup)
{
	if (pickupData[pickup].used) {
		RakNet::BitStream sShowPickupForPlayer;
		sShowPickupForPlayer.Write(pickup);

		for each(playerPool* player in pickupData[pickup].players) {
			NetworkManager->rpc.Signal("HidePickupForPlayer", &sShowPickupForPlayer, HIGH_PRIORITY, RELIABLE_SEQUENCED, 0, netPool.GetPlayerGUID((char*)player->playerusername.c_str()), false, false);
		}

		pickupData[pickup].model = "";
		pickupData[pickup].players.clear();
		pickupData[pickup].used = false;
		pickupData[pickup].x = 0.0f;
		pickupData[pickup].y = 0.0f;
		pickupData[pickup].z = 0.0f;
		pickupData[pickup].interval = 500;
	}

}

void UpdatePickup(int pickup)
{
	RakNet::BitStream sShowPickupForPlayer;
	sShowPickupForPlayer.Write(pickup);

	RakNet::BitStream ShowPickupForPlayer;
	RakNet::RakString string = RakNet::RakString(pickupData[pickup].model.c_str());

	ShowPickupForPlayer.Write(pickup);
	ShowPickupForPlayer.Write(string);
	ShowPickupForPlayer.Write(pickupData[pickup].x);
	ShowPickupForPlayer.Write(pickupData[pickup].y);
	ShowPickupForPlayer.Write(pickupData[pickup].z);
	ShowPickupForPlayer.Write(pickupData[pickup].interval);

	for each(playerPool* player in pickupData[pickup].players) {

		NetworkManager->rpc.Signal("HidePickupForPlayer", &sShowPickupForPlayer, HIGH_PRIORITY, RELIABLE_SEQUENCED, 0, netPool.GetPlayerGUID((char*)player->playerusername.c_str()), false, false);
		NetworkManager->rpc.Signal("ShowPickupForPlayer", &ShowPickupForPlayer, HIGH_PRIORITY, RELIABLE_SEQUENCED, 0, netPool.GetPlayerGUID((char*)player->playerusername.c_str()), false, false);
	}
}
