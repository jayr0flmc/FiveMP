function OnGameModeInit()
	print("My server has started.");
	SetSpawnPoint(-817.657, 178.111, 75.0);
	SetSpawnPoint(-640.183, 297.111, 91.0);
	
	blip = CreateBlip();
	SetBlipLocationType(blip, 0, 0, 10, 70);
	
	return 1;
end

function OnGameModeExit()
	print("My server has stopped.");
	return 1;
end

function OnPlayerConnect(playerid)
	ShowMessageToPlayer(playerid, "Welcome to this ~b~FiveMP ~w~server!");
	ShowMessageToPlayer(playerid, "Your player ID is ~b~" .. math.floor(playerid));
	
	playername = GetPlayerName(playerid);
	ShowMessageToAll("~b~" .. playername .. "(".. math.floor(playerid) .. ") ~w~has connected to the server.");
	
	SetPlayerPos(playerid, 0.0, 10.0, 70.5);
	SetPlayerFacingAngle(playerid, 0.0);
	
	SetPlayerMoney(playerid, 500);
	
	SetPlayerMaxTagDrawDistance(playerid, 100);
	
	SetPlayerHealth(playerid, 100);
	SetPlayerArmour(playerid, 50);
	
	SetPlayerModel(playerid, 0);
	
	GivePlayerWeapon(playerid, "Pistol", 45);
	
	CreateVehicle(playerid, "adder", -3.0, 6.0, 72.0, 360.0, 5, 10, true, 500);
	CreateVehicle(playerid, "banshee", -6.0, 8.0, 72.0, 360.0, 5, 10, true, 500);
	vehicle1 = CreateVehicle(playerid, "infernus", -9.0, 10.0, 72.0, 360.0, 5, 10, true, 500);
	
	ShowBlipForPlayer(blip, playerid);
	
	blip2 = CreateBlip();
	SetBlipLocationType(blip2, 2, playerid);
	ShowBlipForPlayer(blip2, playerid);
	
	
	return 1;
end

function OnPlayerDisconnect(playerid)
	playername = GetPlayerName(playerid);
	ShowMessageToAll("~b~" .. playername .. "(".. math.floor(playerid) .. ") ~w~has left the server.");
	print(playerid .. " has disconnected");
    return 1;
end

function OnPlayerSpawn(playerid)
	print("~b~" .. math.floor(playerid) .. " has spawned");
end

function OnPlayerDeath(playerid)
	playername = GetPlayerName(playerid);
	ShowMessageToAll("~b~" .. playername .. "~w~ has died.");
	print(math.floor(playerid) .. " has dide.");
end
