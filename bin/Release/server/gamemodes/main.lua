function OnGameModeInit()
	print("My server has started.");
	SetSpawnPoint(-817.657, 178.111, 75.0);
	SetSpawnPoint(-640.183, 297.111, 91.0);
	
	CreateVehicle("Adder", -3.0, 6.0, 73.0, 360.0, 5, 10, true, 500);
	vehicle = CreateVehicle("Police", -6.0, 8.0, 73.0, 360.0, 5, 10, true, 500);
	CreateVehicle("Voltic", -9.0, 10.0, 73.0, 360.0, 5, 10, true, 500);
	CreateVehicle("Gargoyle", -12.0, 12.0, 73.0, 360.0, 5, 10, true, 500);
	
	SetVehicleColor(0, 1, 2, 29);
	SetVehicleCustomColor(2, 1, 255, 0, 239);
	SetVehicleNumberPlate(2, "Voltic");
	
	blip = CreateBlip();
	SetBlipLocationType(blip, 1, vehicle);
	SetBlipColor(blip, 23);
	SetBlipImage(blip, 56);
	SetBlipName(blip, "Voltic car");
	
	pickup = CreatePickup();
	SetPickupPos(pickup, -16, 13, 71);
	SetPickupModel(pickup, "prop_ld_health_pack");
	SetPickupRespawnTime(pickup, 2000);
	
	--Known bug, it doesn't create folders!!!!!!
	--Make sure that folders are created.
	inifile = LoadINIFile("test.ini");
	WriteInteger(inifile, "int", 5);
	WriteFloat(inifile, "float", 0.2);
	WriteBoolean(inifile, "boolean", true);
	WriteString(inifile, "string", "testing");
	
	arg1 = ReadInteger(inifile, "int");
	arg2 = ReadFloat(inifile, "float");
	arg3 = ReadBoolean(inifile, "boolean");
	arg4 = ReadString(inifile, "string");
	
	print(arg1);
	print(arg2);
	print(arg3);
	print(arg4);
	
	CloseINIFile(inifile);
	
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
	
	SetPlayerHealth(playerid, 50);
	SetPlayerArmour(playerid, 50);
	SetPlayerModel(playerid, 420);
	
	GivePlayerWeapon(playerid, "Pistol", 45);
	ShowBlipForPlayer(blip, playerid);
	
	ShowPickupForPlayer(pickup, playerid);
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

function OnPlayerPickUpPickup(pickup, player)
	playername = GetPlayerName(player);
	SendMessageToAll("~b~" .. playername .. "~w~ picked up ~b~Pickup");
end

function OnPlayerMessage(playerid, message)
	playername = GetPlayerName(playerid);
	SendMessageToAll( "~r~" .. playername .. "(".. playerid .."): ~w~" .. message);
	return 1;
end

function OnPlayerCommand(playerid, message)
	if message == "/test2" then
		SendMessageToAll("i used the /test2 command which I scripted in my LUA file :D");
		return 1;
	end
	return 0;
end
