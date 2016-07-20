#include "stdafx.h"

void SConfig::Read() {
	CIniReader iniReader(".\\FiveMP.ini");

	ServerPort			= iniReader.ReadString("Connection", "port", "");

	ScriptGameMode		= iniReader.ReadString("Scripts", "gamemode", "");

	ServerName			= iniReader.ReadString("Details", "servername", "");
	MaxPlayers			= iniReader.ReadInteger("Details", "maxplayers", 32);

	ServerTimeHour		= iniReader.ReadInteger("Details", "hour", 12);
	ServerTimeMinute	= iniReader.ReadInteger("Details", "min", 00);
	ServerTimeScale		= iniReader.ReadFloat("Details", "timescale", 2.0);
	ServerTimeFreeze	= iniReader.ReadBoolean("Details", "freeze", false);
	ServerWeather		= iniReader.ReadString("Details", "weather", "");
}
