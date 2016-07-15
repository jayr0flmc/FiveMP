#include "stdafx.h"

bool GameVehicle::CreateVehicle(int vehicleid, char *modelname, Vector3 coords, float heading, int color1, int color2, bool respawn, int respawndelay)
{
	vehicleData[vehicleid].vehicleModel = GAMEPLAY::GET_HASH_KEY(modelname);

	if (STREAMING::IS_MODEL_IN_CDIMAGE(vehicleData[vehicleid].vehicleModel) && STREAMING::IS_MODEL_VALID(vehicleData[vehicleid].vehicleModel))
	{
		STREAMING::REQUEST_MODEL(vehicleData[vehicleid].vehicleModel);
		while (!STREAMING::HAS_MODEL_LOADED(vehicleData[vehicleid].vehicleModel))
			WAIT(0);
		vehicleData[vehicleid].vehicleVehicle = VEHICLE::CREATE_VEHICLE(vehicleData[vehicleid].vehicleModel, coords.x, coords.y, coords.z, heading, false, true);
		STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(vehicleData[vehicleid].vehicleModel);

		VEHICLE::SET_VEHICLE_COLOURS(vehicleData[vehicleid].vehicleVehicle, color1, color2);

		vehicleData[vehicleid].used = true;
		return 1;
	}
	return 0;
}

bool GameVehicle::SetVehicleColor(int vehicleid, int color1, int color2)
{
	if (ENTITY::DOES_ENTITY_EXIST(vehicleData[vehicleid].vehicleVehicle))
	{
		VEHICLE::SET_VEHICLE_COLOURS(vehicleData[vehicleid].vehicleVehicle, color1, color2);

		vehicleData[vehicleid].vehicleColor1 = color1;
		vehicleData[vehicleid].vehicleColor2 = color2;

		return 1;
	}
	return 0;
}