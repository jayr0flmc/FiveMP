function OnGameModeInit()
	print("My server has started.");
	SetSpawnPoint(-817.657, 178.111, 75.0);
	SetSpawnPoint(-640.183, 297.111, 91.0);
	
	CreateVehicle("Adder", -3.0, 6.0, 73.0, 360.0, 5, 10, true, 500);
	CreateVehicle("Police", -6.0, 8.0, 73.0, 360.0, 5, 10, true, 500);
	vehicle = CreateVehicle("Voltic", -9.0, 10.0, 73.0, 360.0, 5, 10, true, 500);
	CreateVehicle("Gargoyle", -12.0, 12.0, 73.0, 360.0, 5, 10, true, 500);
	
	blip = CreateBlip();
	SetBlipLocationType(blip, 1, vehicle);
	SetBlipColor(blip, 1);
	
	return 1;
end

function OnGameModeExit()
	print("My server has stopped.");
	return 1;
end

function OnPlayerConnect(playerid)
	ShowMessageToPlayer(playerid, "Welcome to this ~b~FiveMP ~w~server!");
	ShowMessageToPlayer(playerid, "Your player ID is ~b~" .. playerid);
	
	playername = GetPlayerName(playerid);
	ShowMessageToAll("~b~" .. playername .. "(".. playerid .. ") ~w~has connected to the server.");
	
	SetPlayerPos(playerid, 0.0, 0.0, 73.5);
	SetPlayerFacingAngle(playerid, 45.0);
	
	SetPlayerMoney(playerid, 500);
	
	SetPlayerMaxTagDrawDistance(playerid, 50);
	
	SetPlayerHealth(playerid, 100);
	SetPlayerArmour(playerid, 50);
	
	SetPlayerModel(playerid, 420);
	
	--SetPlayerComponentVariation(playerid, 3, 1, 1, 1);
	--SetPlayerComponentVariation(playerid, 2, 10, 1, 1);
	
	GivePlayerWeapon(playerid, "Pistol", 45);
	
	ShowBlipForPlayer(blip, playerid);
	
	SendMessageToPlayer(playerid, "this is a test1");
	SendMessageToPlayer(playerid, "this is a test2");
	SendMessageToPlayer(playerid, "this is a test3");
	SendMessageToPlayer(playerid, "this is a test4");
	SendMessageToPlayer(playerid, "this is a test5");
	SendMessageToPlayer(playerid, "this is a test6");
	SendMessageToPlayer(playerid, "this is a test7");
	SendMessageToPlayer(playerid, "this is a test8");
	SendMessageToPlayer(playerid, "this is a test9");
	SendMessageToPlayer(playerid, "this is a test10");
	SendMessageToPlayer(playerid, "this is a test11");
	return 1;
end

function OnPlayerDisconnect(playerid)
	playername = GetPlayerName(playerid);
	ShowMessageToAll("~b~" .. playername .. "(".. playerid .. ") ~w~has left the server.");
	print(playerid .. " has disconnected");
    return 1;
end

function OnPlayerSpawn(playerid)
	print("~b~" .. playerid .. " has spawned");
end

function OnPlayerDeath(playerid)
	playername = GetPlayerName(playerid);
	ShowMessageToAll("~b~" .. playername .. "(".. playerid .. ")~w~ has died.");
	print(playerid .. " has died.");
end
