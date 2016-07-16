#include "stdafx.h"

SPlayer::SPlayer()
{
}

SPlayer::~SPlayer()
{
}

void SPlayer::Player()
{
	PlayerPulse();
}

void SPlayer::PlayerPulse()
{
		for (int i = 0; i < 100; i++) {
			if (playerData[i].used == true) {
				if (playerData[i].pedHealth <= 0 && playerData[i].dead == false)
				{
					OnPlayerDeath(sLUA, playerData[i].playerid);
					playerData[i].dead = true;
				}


				if (playerData[i].pedHealth > 0 && playerData[i].dead == true) {
					float closest = 0;
					int spawnid = 0;

					for (int s = 0; s < 50; s++) {
						if (spawnData[s].used == true)
						{
							float tempd = Distance(playerData[i].x, spawnData[s].x, playerData[i].y, spawnData[s].y, playerData[i].z, spawnData[s].z);

							if (s == 0 || closest > tempd) {
								closest = tempd;
								spawnid = s;
							}
						}
					}

					SpawnPlayer(i, spawnid, spawnData[spawnid].x, spawnData[spawnid].y, spawnData[spawnid].z);
					playerData[i].dead = false;
				}
			}
		}
}

void SPlayer::SpawnPlayer(int playerid, int spawnid, float x, float y, float z ) {

	if (spawnData[spawnid].used)
	{
		RakNet::BitStream sSetPlayerPos;
		sSetPlayerPos.Write(playerid);
		sSetPlayerPos.Write(x);
		sSetPlayerPos.Write(y);
		sSetPlayerPos.Write(z);
		NetworkManager->rpc.Signal("SetPlayerPos", &sSetPlayerPos, HIGH_PRIORITY, RELIABLE_SEQUENCED, 0, netPool.GetPlayerGUIDfromId(playerid), false, false);
	}

	OnPlayerSpawn(sLUA, playerid);
}

float SPlayer::Distance(float x1, float x2, float y1, float y2, float z1, float z2)
{
	float dx = x2 - x1;
	float dy = y2 - y1;
	float dz = z2 - z1;

	return sqrt(dx * dx + dy * dy + dz * dz);;
}

void SPlayer::UpdatePlayerNickMaxDistance(int playerid)
{
	RakNet::BitStream sSetMaxNickDrawDistance;
	sSetMaxNickDrawDistance.Write(playerid);
	sSetMaxNickDrawDistance.Write(playerData[playerid].maxNickDistance);
	NetworkManager->rpc.Signal("SetPlayerMaxNickDrawDistance", &sSetMaxNickDrawDistance, HIGH_PRIORITY, RELIABLE_SEQUENCED, 0, netPool.GetPlayerGUIDfromId(playerid), false, false);
}
