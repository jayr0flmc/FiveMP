#include "stdafx.h"

SPlayer::SPlayer()
{
}

SPlayer::~SPlayer()
{
}

void SPlayer::PlayerSpawn()
{
	for (int i = 0; i < sizeof(playerData) / sizeof(*playerData); i++) {
		if (playerData[i].pedHealth <= 0)
		{
			OnPlayerDeath(sLUA, i);

			float closest = 0;
			int id = 0;

			for (int s = 0; s < sizeof(spawnData) / sizeof(*spawnData); s++) {

				float tempd = Distance(playerData[i].x, spawnData[s].x, playerData[i].y, spawnData[s].y, playerData[i].z, spawnData[s].z);

				if (s = 0 || closest > tempd) {
					closest = tempd;
					id = s;
				}
			}

			RakNet::BitStream sSetPlayerPos;
			sSetPlayerPos.Write(i);
			sSetPlayerPos.Write(spawnData[id].x);
			sSetPlayerPos.Write(spawnData[id].y);
			sSetPlayerPos.Write(spawnData[id].z);
			NetworkManager->rpc.Signal("SetPlayerPos", &sSetPlayerPos, HIGH_PRIORITY, RELIABLE_SEQUENCED, 0, netPool.GetPlayerGUIDfromId(i), false, false);

			playerData[i].pedHealth = 100;
			OnPlayerSpawn(sLUA, i);
		}
	}
}

float SPlayer::Distance(float x1, float x2, float y1, float y2, float z1, float z2)
{
	float dx = x2 - x1;
	float dy = y2 - y1;
	float dz = z2 - z1;

	return sqrt(dx * dx + dy * dy + dz * dz);;
}
