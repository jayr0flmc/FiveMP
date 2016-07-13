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
		for (int i = 0; i < sizeof(playerData) / sizeof(*playerData); i++) {

			if (playerData[i].pedHealth <= 0 && playerData[i].dead == false && playerData[i].used == true)
			{
				OnPlayerDeath(sLUA, playerData[i].playerid);
				playerData[i].dead = true;
			}


			if (playerData[i].pedHealth > 0 && playerData[i].dead == true && playerData[i].used == true) {
				float closest = 0;
				int spawnid = 0;

				for (int s = 0; s < sizeof(spawnData) / sizeof(*spawnData); s++) {
					if (spawnData[s].used == true)
					{
						float tempd = Distance(playerData[i].x, spawnData[s].x, playerData[i].y, spawnData[s].y, playerData[i].z, spawnData[s].z);

						if (s == 0 || closest > tempd) {
							closest = tempd;
							spawnid = s;
						}
					}
				}

				playerData[i].dead = false;
				SpawnPlayer(i, spawnid);
			}
		}
}

void SPlayer::SpawnPlayer(int playerid, int spawnid) {

		RakNet::BitStream sSetPlayerPos;
		sSetPlayerPos.Write(playerid);
		sSetPlayerPos.Write(spawnData[spawnid].x);
		sSetPlayerPos.Write(spawnData[spawnid].y);
		sSetPlayerPos.Write(spawnData[spawnid].z);
		NetworkManager->rpc.Signal("SetPlayerPos", &sSetPlayerPos, HIGH_PRIORITY, RELIABLE_SEQUENCED, 0, netPool.GetPlayerGUIDfromId(playerid), false, false);

		OnPlayerSpawn(sLUA, playerid);
}

float SPlayer::Distance(float x1, float x2, float y1, float y2, float z1, float z2)
{
	float dx = x2 - x1;
	float dy = y2 - y1;
	float dz = z2 - z1;

	return sqrt(dx * dx + dy * dy + dz * dz);;
}
