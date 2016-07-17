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

void GameVehicle::RemoveVehicle(int vehicleid)
{
	if (ENTITY::DOES_ENTITY_EXIST(vehicleData[vehicleid].vehicleVehicle)) {

		ENTITY::DELETE_ENTITY(&vehicleData[vehicleid].vehicleVehicle);
		UI::REMOVE_BLIP(&vehicleData[vehicleid].vehicleBlip);
	}
	vehicleData[vehicleid].used = false;
}

void GameVehicle::SetVehicleColor(int vehicleid, int color1, int color2)
{
	if (ENTITY::DOES_ENTITY_EXIST(vehicleData[vehicleid].vehicleVehicle))
	{
		VEHICLE::SET_VEHICLE_COLOURS(vehicleData[vehicleid].vehicleVehicle, color1, color2);

		vehicleData[vehicleid].vehicleColor1 = color1;
		vehicleData[vehicleid].vehicleColor2 = color2;
	}
}

void GameVehicle::SetVehicleCustomColor(int vehicleid, int layer, int r, int g, int b)
{
	if (ENTITY::DOES_ENTITY_EXIST(vehicleData[vehicleid].vehicleVehicle))
	{
		if (layer == 1) {
			VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(vehicleData[vehicleid].vehicleVehicle, r, g, b);
		}

		if (layer == 2) {
			VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(vehicleData[vehicleid].vehicleVehicle, r, g, b);
		}
	}
}