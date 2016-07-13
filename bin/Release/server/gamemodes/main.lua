function OnGameModeInit()
	print("My server has started.");
	return 1;
end

function OnGameModeExit()
	print("My server has stopped.");
	return 1;
end

function OnPlayerConnect(playerid)
	GivePlayerWeapon(playerid, "Pistol", 45);
	ShowMessageToPlayer(playerid, "Welcome to this ~b~FiveMP ~w~server!");
	ShowMessageToPlayer(playerid, "Your player ID is ~b~" .. playerid);
	
	SetPlayerPos(playerid, 0.0, 0.0, 70.5);
	SetPlayerFacingAngle(playerid, 0.0);
	
	SetPlayerMoney(playerid, 500);
	return 1;
end

function OnPlayerDisconnect(playerid)
	print(playerid .. " has disconnected");
    return 1;
end

