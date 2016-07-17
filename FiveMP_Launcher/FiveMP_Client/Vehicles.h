#pragma once
class GameVehicle
{
public:
	bool CreateVehicle(int vehicleid, char *modelname, Vector3 coords, float heading, int color1, int color2, bool respawn, int respawndelay);
	void RemoveVehicle(int vehicleid);
	void SetVehicleColor(int vehicleid, int color1, int color2);
	void SetVehicleCustomColor(int vehicleid, int layer, int r, int g, int b);
};

