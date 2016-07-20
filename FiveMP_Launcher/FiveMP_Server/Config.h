#pragma once
class SConfig
{
public:
	char	*ServerPort;

	char	*ScriptGameMode;
	char	*ServerName;
	int		MaxPlayers;

	int		ServerTimeHour;
	int		ServerTimeMinute;
	float	ServerTimeScale;
	bool	ServerTimeFreeze;
	char	*ServerWeather;

	void	Read();
};