#include "stdafx.h"
#include <ctime>

clock_t begin_time = clock();

SWorld::SWorld()
{
}

SWorld::~SWorld()
{
}

void SWorld::StartTime() {
	
}

void SWorld::UpdateTime() {
	
	float cseconds = float(clock() - begin_time) / CLOCKS_PER_SEC;

	if (cseconds >= Config->ServerTimeScale) {
		begin_time = clock();

		if (Config->ServerTimeMinute < 60)
		{
			Config->ServerTimeMinute += 1;
		}
		else
		{
			Config->ServerTimeMinute = 0;
			if (Config->ServerTimeHour < 23)
				Config->ServerTimeHour += 1;
			else
				Config->ServerTimeHour = 0;
		}

		RakNet::BitStream sSetTime;
		sSetTime.Write(Config->ServerTimeHour);
		sSetTime.Write(Config->ServerTimeMinute);
		sSetTime.Write(0);
		NetworkManager->rpc.Signal("SetTime", &sSetTime, LOW_PRIORITY, RELIABLE_ORDERED, 0, RakNet::UNASSIGNED_SYSTEM_ADDRESS, true, false);
	}
	/*
	else {
		if (seconds < 60) {
			seconds += Config->ServerTimeScale / 60 ;
			
			if (lastSecond != seconds) {
				RakNet::BitStream sSetTime;
				sSetTime.Write(Config->ServerTimeHour);
				sSetTime.Write(Config->ServerTimeMinute);
				sSetTime.Write(seconds);
				NetworkManager->rpc.Signal("SetTime", &sSetTime, HIGH_PRIORITY, RELIABLE_ORDERED, 0, RakNet::UNASSIGNED_SYSTEM_ADDRESS, true, false);
			}
		}
		else {
			seconds = 0;
		}
	}
	*/
}