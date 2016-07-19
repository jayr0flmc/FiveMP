#include "stdafx.h"

SNetworkManager *NetworkManager;
SRPCManager		*RPCManager;
SASIManager		*ASIManager;
SConfig			*Config;
SPlayer			*PlayerManager;
SVehicle		*VehicleManager;
SWorld			*WorldManager;

int userAmount, vehicleAmount;
char userGuid;

playerPool playerData[100];
spawnPool spawnData[50];
vehiclePool vehicleData[150];
blipPool blipData[100];
pickupPool pickupData[100];

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

	ASIManager = new SASIManager;

	PlayerManager = new SPlayer;
	VehicleManager = new SVehicle;
	WorldManager = new SWorld;

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
	lua_register(sLUA, "IsPlayerConnected", IsPlayerConnected);
	lua_register(sLUA, "SetPlayerComponentVariation", SetPedComponentVariation);

	// Player (UI)
	lua_register(sLUA, "ShowMessageToPlayer", ShowMessageToPlayer);
	lua_register(sLUA, "ShowMessageToAll", ShowMessageToAll);
	lua_register(sLUA, "SendMessageToPlayer", SendMessageToPlayer);
	lua_register(sLUA, "SendMessageToAll", SendMessageToAll);

	// Weapon
	lua_register(sLUA, "GivePlayerWeapon", GivePlayerWeapon);
	lua_register(sLUA, "RemovePlayerWeapon", RemovePlayerWeapon);
	lua_register(sLUA, "RemovePlayerWeapons", RemovePlayerWeapons);
	lua_register(sLUA, "GivePlayerAmmo", GivePlayerAmmo);
	lua_register(sLUA, "RemovePlayerAmmo", RemovePlayerAmmo);

	// Server
	lua_register(sLUA, "GetTime", GetTime);
	lua_register(sLUA, "SetTime", SetTime);
	lua_register(sLUA, "SetSpawnPoint", SetSpawnPoint);
	lua_register(sLUA, "RemoveSpawnPoint", RemoveSpawnPoint);

	// Vehicle
	lua_register(sLUA, "CreateVehicle", CreateVehicle);
	lua_register(sLUA, "RemoveVehicle", RemoveVehicle);
	lua_register(sLUA, "SetVehicleColor", SetVehicleColor);
	lua_register(sLUA, "SetVehicleCustomColor", SetVehicleCustomColor);
	lua_register(sLUA, "SetVehicleNumberPlate", SetVehicleNumberPlate);

	//Blips
	lua_register(sLUA, "CreateBlip", CreateBlip);
	lua_register(sLUA, "SetBlipLocationType", SetBlipLocationType);
	lua_register(sLUA, "ShowBlipForPlayer", ShowBlipForPlayer);
	lua_register(sLUA, "HideBlipForPlayer", HideBlipForPlayer);
	lua_register(sLUA, "RemoveBlip", RemoveBlip);
	lua_register(sLUA, "SetBlipColor", SetBlipColor);
	lua_register(sLUA, "SetBlipName", SetBlipName);
	lua_register(sLUA, "SetBlipImage", SetBlipImage);
	lua_register(sLUA, "GetBlipLocationType", GetBlipLocationType);
	lua_register(sLUA, "GetBlipColor", GetBlipColor);
	lua_register(sLUA, "GetBlipImage", GetBlipImage);
	lua_register(sLUA, "GetBlipName", GetBlipName);

	lua_register(sLUA, "RemoveDefaultBlipFromPlayer", RemoveDefaultBlipFromPlayer);
	lua_register(sLUA, "IsDefaultBlipRemovedFromPlayer", IsDefaultBlipRemovedFromPlayer);

	//Pickups
	lua_register(sLUA, "CreatePickup", CreatePickup);
	lua_register(sLUA, "RemovePickup", RemovePickup);
	lua_register(sLUA, "SetPickupPos", SetPickupPos);
	lua_register(sLUA, "SetPickupModel", SetPickupModelID);
	lua_register(sLUA, "ShowPickupForPlayer", ShowPickupForPlayer);
	lua_register(sLUA, "HidePickupForPlayer", HidePickupForPlayer);
	lua_register(sLUA, "SetPickupRespawnTime", SetPickupRespawnTime);

	OnGameModeInit(sLUA);

	char message[256];

	while (1)
	{
		NetworkManager->Pulse();
		PlayerManager->Player();
		if(!Config->ServerTimeFreeze)
			WorldManager->UpdateTime();

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