#pragma once
class GameWorld {
public:
	void CleanUp();
	void SetTime(int hour, int minute, int seconds);
	void SetWeather(char *weather, int time);
};