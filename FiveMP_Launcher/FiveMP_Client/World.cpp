#pragma once

#include "stdafx.h"

void GameWorld::CleanUp() {

	for (int i = 0; i < sizeof(playerData) / sizeof(*playerData); i++) {
		if (ENTITY::DOES_ENTITY_EXIST(playerData[i].pedPed)) {
			ENTITY::DELETE_ENTITY(&playerData[i].pedPed);
			UI::REMOVE_BLIP(&playerData[i].pedBlip);
		}
	}

	for (int i = 0; i < sizeof(vehicleData) / sizeof(*vehicleData); i++ ) {
		if (ENTITY::DOES_ENTITY_EXIST(vehicleData[i].vehicleVehicle)) {

			ENTITY::DELETE_ENTITY(&vehicleData[i].vehicleVehicle);
			UI::REMOVE_BLIP(&vehicleData[i].vehicleBlip);

			vehicleData[i].used = false;
		}
	}

	for (int i = 0; i < sizeof(blipData) / sizeof(*blipData); i++) {
		if (UI::DOES_BLIP_EXIST(blipData[i].blip)) {
			UI::REMOVE_BLIP(&blipData[i].blip);
			blipData[i].used = false;
		}
	}
}