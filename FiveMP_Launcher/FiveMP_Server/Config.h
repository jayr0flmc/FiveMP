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
	bool	ServerTimeFreeze;

	void	Read();
};