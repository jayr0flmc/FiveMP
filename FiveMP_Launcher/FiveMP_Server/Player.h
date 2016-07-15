#pragma once
class SPlayer
{
public:
	SPlayer();
	~SPlayer();

	void	Player();
	void	PlayerPulse();
	void	SpawnPlayer(int playerid, int spawnid);
	float	Distance(float x1, float x2, float y1, float y2, float z1, float z2);
	void	UpdatePlayerNickMaxDistance(int playerid);
};