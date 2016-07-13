#pragma once
class SPlayer
{
public:
	SPlayer();
	~SPlayer();

	void	PlayerSpawn();
	float	Distance(float x1, float x2, float y1, float y2, float z1, float z2);
};