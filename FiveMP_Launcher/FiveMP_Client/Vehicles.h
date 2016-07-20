#pragma once
class GameVehicle
{
public:
	bool CreateVehicle(int vehicleid, char *modelname, Vector3 coords, float heading, int color1, int color2, bool respawn, int respawndelay);
	void RemoveVehicle(int vehicleid);
	void SetVehicleColor(int vehicleid, int layer, int color, int painttype);
	void SetVehicleCustomColor(int vehicleid, int layer, int r, int g, int b);
	void SetVehicleNumberPlate(int vehicleid, const char* plate);
};

