#pragma once

class GamePlayer {
public:
	void ShowMessageAboveMap(char * msg);
	char *GetPlayerSocialClubName();
	void SetMoney(int money);

	void DisableScripts();

	bool usingChat = false;
};