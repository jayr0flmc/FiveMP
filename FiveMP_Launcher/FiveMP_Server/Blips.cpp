#include "stdafx.h"

void RemoveBlip(int blip)
{
	if (blipData[blip].used) {
		RakNet::BitStream sShowBlipForPlayer;
		sShowBlipForPlayer.Write(blip);

		for each(playerPool* player in blipData[blip].players) {
			NetworkManager->rpc.Signal("HideBlipForPlayer", &sShowBlipForPlayer, HIGH_PRIORITY, RELIABLE_SEQUENCED, 0, netPool.GetPlayerGUID((char*)player->playerusername.c_str()), false, false);
		}

		blipData[blip].attachID = 0;
		blipData[blip].color = 0;
		blipData[blip].players.clear();
		blipData[blip].used = false;
		blipData[blip].x = 0.0f;
		blipData[blip].y = 0.0f;
		blipData[blip].z = 0.0f;
		blipData[blip].locationType = 0;
		blipData[blip].name = std::string("");
		blipData[blip].spriteid = 0;
	}
}

void UpdateBlip(int blip)
{
	RakNet::BitStream ssShowBlipForPlayer;
	ssShowBlipForPlayer.Write(blip);

	RakNet::BitStream sShowBlipForPlayer;
	RakNet::RakString string = RakNet::RakString(blipData[blip].name.c_str());

	sShowBlipForPlayer.Write(blip);
	sShowBlipForPlayer.Write(blipData[blip].locationType);
	sShowBlipForPlayer.Write(blipData[blip].x);
	sShowBlipForPlayer.Write(blipData[blip].y);
	sShowBlipForPlayer.Write(blipData[blip].z);
	sShowBlipForPlayer.Write(blipData[blip].attachID);
	sShowBlipForPlayer.Write(blipData[blip].color);
	sShowBlipForPlayer.Write(blipData[blip].spriteid);
	sShowBlipForPlayer.Write(string);

	for each(playerPool* player in pickupData[blip].players) {

		NetworkManager->rpc.Signal("HideBlipForPlayer", &ssShowBlipForPlayer, HIGH_PRIORITY, RELIABLE_SEQUENCED, 0, netPool.GetPlayerGUID((char*)player->playerusername.c_str()), false, false);
		NetworkManager->rpc.Signal("ShowBlipForPlayer", &sShowBlipForPlayer, HIGH_PRIORITY, RELIABLE_SEQUENCED, 0, netPool.GetPlayerGUID((char*)player->playerusername.c_str()), false, false);
	}
}
