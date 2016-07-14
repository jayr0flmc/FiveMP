#include "stdafx.h"

SNetworkManager *NetworkManager;
SRPCManager		*RPCManager;
SConfig			*Config;
SPlayer			*PlayerManager;

int userAmount, vehicleAmount;
char userGuid;

playerPool playerData[100];
spawnPool spawnData[50];

int main(void)
{
	Config = new SConfig;

	Config->Read();

	printf("\n%s starting on Port: %s - time: %d - %d - %d\n", Config->ServerName, Config->ServerPort, Config->ServerTimeHour, Config->ServerTimeMinute, Config->ServerTimeFreeze);

	SetConsoleTitle("FiveMP - Server Console");

	puts("Starting server.");

	char tempgamemode[64];
	sprintf(tempgamemode, "gamemodes//%s.lua", Config->ScriptGameMode);

	NetworkManager = new SNetworkManager;
	NetworkManager->Start();
	RPCManager = new SRPCManager;
	RPCManager->RegisterRPCs();
	PlayerManager = new SPlayer;

	sLUA = luaL_newstate();
	luaL_openlibs(sLUA);
	luaL_dofile(sLUA, tempgamemode);

	// Player
	lua_register(sLUA, "SetPlayerName", SetPlayerName);
	lua_register(sLUA, "GetPlayerName", GetPlayerName);
	lua_register(sLUA, "SetPlayerMoney", SetPlayerMoney);
	lua_register(sLUA, "GivePlayerMoney", GivePlayerMoney);
	lua_register(sLUA, "GetPlayerMoney", GetPlayerMoney);
	lua_register(sLUA, "KickPlayer", KickPlayer);
	lua_register(sLUA, "SetPlayerPos", SetPlayerPos);
	lua_register(sLUA, "GetPlayerPos", GetPlayerPos);
	lua_register(sLUA, "SetPlayerFacingAngle", SetPlayerFacingAngle);
	lua_register(sLUA, "GetPlayerFacingAngle", GetPlayerFacingAngle);
	lua_register(sLUA, "SetPlayerScore", SetPlayerScore);
	lua_register(sLUA, "GivePlayerScore", GivePlayerScore);
	lua_register(sLUA, "GetPlayerScore", GetPlayerScore);
	lua_register(sLUA, "SetPlayerHealth", SetPlayerHealth);
	lua_register(sLUA, "GetPlayerHealth", GetPlayerHealth);
	lua_register(sLUA, "SetPlayerArmour", SetPlayerArmour);
	lua_register(sLUA, "GetPlayerArmour", GetPlayerArmour);
	lua_register(sLUA, "SetPlayerMaxTagDrawDistance", SetPlayerMaxNickDrawDistance);
	lua_register(sLUA, "SetPlayerModel", SetPlayerModel);
	lua_register(sLUA, "GetPlayerModel", GetPlayerModel);

	// Player (UI)
	lua_register(sLUA, "ShowMessageToPlayer", ShowMessageToPlayer);

	// Weapon
	lua_register(sLUA, "GivePlayerWeapon", GivePlayerWeapon);
	lua_register(sLUA, "RemovePlayerWeapon", RemovePlayerWeapon);
	lua_register(sLUA, "GivePlayerAmmo", GivePlayerAmmo);
	lua_register(sLUA, "RemovePlayerAmmo", RemovePlayerAmmo);

	// Server
	lua_register(sLUA, "GetTime", GetTime);
	lua_register(sLUA, "SetTime", SetTime);

	//World
	lua_register(sLUA, "SetSpawnPoint", SetSpawnPoint);

	OnGameModeInit(sLUA);

	char message[256];

	while (1)
	{
		NetworkManager->Pulse();
		PlayerManager->Player();

		if (_kbhit())
		{
			Gets(message, sizeof(message));

			if (strcmp(message, "quit") == 0)
			{
				puts("Quitting.");
				break;
			}

			if (strcmp(message, "playertest") == 0)
			{
				printf("%d - %s - %s", playerData[0].playerid, playerData[0].playerusername, playerData[0].playerguid);
				break;
			}

			if (strcmp(message, "stat") == 0)
			{
				NetworkManager->rss = NetworkManager->server->GetStatistics(NetworkManager->server->GetSystemAddressFromIndex(0));
				StatisticsToString(NetworkManager->rss, message, 2);
				printf("%s", message);
				printf("Ping %i\n", NetworkManager->server->GetAveragePing(NetworkManager->server->GetSystemAddressFromIndex(0)));

				continue;
			}

			if (strcmp(message, "playerlist") == 0)
			{
				RakNet::SystemAddress systems[10];
				unsigned short numConnections = Config->MaxPlayers;
				NetworkManager->server->GetConnectionList((RakNet::SystemAddress*) &systems, &numConnections);
				for (int i = 0; i < numConnections; i++)
				{
					printf("%i. %s\n", i + 1, systems[i].ToString(true));
				}
				continue;
			}

			if (strcmp(message, "ban") == 0)
			{
				printf("Enter IP to ban.  You can use * as a wildcard\n");
				Gets(message, sizeof(message));
				NetworkManager->server->AddToBanList(message);
				printf("IP %s added to ban list.\n", message);

				continue;
			}

			char message2[2048];

			message2[0] = 0;
			const static char prefix[] = "~b~Server:~w~ ";
			strncpy(message2, prefix, sizeof(message2));
			strncat(message2, message, sizeof(message2) - strlen(prefix) - 1);

			NetworkManager->server->Send(message2, (const int)strlen(message2) + 1, HIGH_PRIORITY, RELIABLE_ORDERED, 0, RakNet::UNASSIGNED_SYSTEM_ADDRESS, true);
		}
	}

	OnGameModeExit(sLUA);
	lua_close(sLUA);
	
	Sleep(2500);
	return 0;
}