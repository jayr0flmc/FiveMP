function OnGameModeInit()
	print("My server has started.");
	SetSpawnPoint(-817.657, 178.111, 75.0);
	SetSpawnPoint(-640.183, 297.111, 100.0);
	return 1;
end

function OnGameModeExit()
	print("My server has stopped.");
	return 1;
end

function OnPlayerConnect(playerid)
	ShowMessageToPlayer(playerid, "Welcome to this ~b~FiveMP ~w~server!");
	ShowMessageToPlayer(playerid, "Your player ID is ~b~" .. playerid);
	
	SetPlayerPos(playerid, 0.0, 0.0, 70.5);
	SetPlayerFacingAngle(playerid, 0.0);
	
	SetPlayerMoney(playerid, 500);
	
	SetPlayerMaxTagDrawDistance(playerid, 100);
	
	SetPlayerHealth(playerid, 100);
	SetPlayerArmour(playerid, 50);
	
	SetPlayerModel(playerid, 23);
	GivePlayerWeapon(playerid, "Firework", 45);
	return 1;
end

function OnPlayerDisconnect(playerid)
	print(playerid .. " has disconnected");
    return 1;
end

function OnPlayerSpawn(playerid)
	print(playerid .. " Spawned");
	
	SetPlayerModel(playerid, 24);
end

function OnPlayerDeath(playerid)
	print(playerid .. " Died");
end
