#pragma once
class SWorld
{
public:
	SWorld();
	~SWorld();

	float seconds = 0;
	float lastSecond = 0;

	void	StartTime();
	void	UpdateTime();
};