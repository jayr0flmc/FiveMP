function OnGameModeInit()
	print("My server has started.");
	SetSpawnPoint(-817.657, 178.111, 75.0);
	SetSpawnPoint(-640.183, 297.111, 91.0);
	
	CreateVehicle("Adder", -3.0, 6.0, 73.0, 360.0, 5, 10, true, 500);
	CreateVehicle("Police", -6.0, 8.0, 73.0, 360.0, 5, 10, true, 500);
	CreateVehicle("Voltic", -9.0, 10.0, 73.0, 360.0, 5, 10, true, 500);
	CreateVehicle("Gargoyle", -12.0, 12.0, 73.0, 360.0, 5, 10, true, 500);
	
	-- Blips are causing issues at the moment, not recommend to use.
	--blip = CreateBlip();
	--SetBlipLocationType(blip, 1, vehicle);
	--SetBlipColor(blip, 23);
	--SetBlipImage(blip, 56);
	--SetBlipName(blip, "Voltic car");
	return 1;
end

function OnGameModeExit()
	print("My server has stopped.");
	return 1;
end

function OnPlayerConnect(playerid)
	playername = GetPlayerName(playerid);
	SendMessageToAll("~b~" .. playername .. "(".. playerid .. ") ~w~has connected to the server.");

	SendMessageToPlayer(playerid, "Hi there ~b~"..playername.. "~w~, welcome to this Five~r~MP ~w~server!");
	SendMessageToPlayer(playerid, "Your player ID is ~b~" .. playerid);
	
	SetPlayerPos(playerid, 0.0, 0.0, 73.5);
	SetPlayerFacingAngle(playerid, 45.0);
	
	SetPlayerMoney(playerid, 500);
	SetPlayerMaxTagDrawDistance(playerid, 50);
	
	SetPlayerHealth(playerid, 100);
	SetPlayerArmour(playerid, 50);
	SetPlayerModel(playerid, 420);
	
	GivePlayerWeapon(playerid, "Pistol", 45);
	ShowBlipForPlayer(blip, playerid);
	return 1;
end

function OnPlayerDisconnect(playerid)
	playername = GetPlayerName(playerid);
	SendMessageToAll("~b~" .. playername .. "(".. playerid .. ") ~w~has left the server.");
	print(playerid .. " has disconnected");
    return 1;
end

function OnPlayerSpawn(playerid)
	print("~b~" .. playerid .. " has spawned");
	return 1;
end

function OnPlayerDeath(playerid)
	playername = GetPlayerName(playerid);
	SendMessageToAll("~b~" .. playername .. "(".. playerid .. ")~w~ has died.");
	print(playerid .. " has died.");
	return 1;
end


function OnPlayerUpdate(playerid)
	--SetPlayerArmour(playerid, 100);
	--Disabling it because it really spams the console :D
	return 1;
end
