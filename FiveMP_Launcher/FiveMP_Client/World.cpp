#pragma once

#include "stdafx.h"

void GameWorld::CleanUp() {

	for (int i = 0; i < sizeof(playerData) / sizeof(*playerData); i++) {
		if (ENTITY::DOES_ENTITY_EXIST(playerData[i].pedPed)) {
			AI::TASK_LEAVE_VEHICLE(playerData[i].pedPed, vehicleData[playerData[i].vehicleid].vehicleVehicle, 16);
			playerData[i].vehicleid = -1;

			PED::DELETE_PED(&playerData[i].pedPed);
			ENTITY::DELETE_ENTITY(&playerData[i].pedPed);
			UI::REMOVE_BLIP(&playerData[i].pedBlip);
		}
	}

	for (int i = 0; i < sizeof(vehicleData) / sizeof(*vehicleData); i++ ) {
		if (ENTITY::DOES_ENTITY_EXIST(vehicleData[i].vehicleVehicle)) {
			VEHICLE::DELETE_VEHICLE(&vehicleData[i].vehicleVehicle);
			ENTITY::DELETE_ENTITY(&vehicleData[i].vehicleVehicle);
			UI::REMOVE_BLIP(&vehicleData[i].vehicleBlip);

			vehicleData[i].playerid = -1;
			vehicleData[i].used = false;
		}
	}

	for (int i = 0; i < sizeof(blipData) / sizeof(*blipData); i++) {
		if (UI::DOES_BLIP_EXIST(blipData[i].blip)) {
			UI::REMOVE_BLIP(&blipData[i].blip);

			blipData[i].used = false;
		}
	}

	for (int i = 0; i < sizeof(pickupData) / sizeof(*pickupData); i++) {
		if (OBJECT::DOES_PICKUP_EXIST(pickupData[i].pickup)) {
			OBJECT::REMOVE_PICKUP(pickupData[i].pickup);

			pickupData[i].used = false;
		}
	}
}

void GameWorld::SetTime(int hour, int minute, int seconds) {
	TIME::SET_CLOCK_TIME(hour, minute, seconds);
}

void GameWorld::SetWeather(char * weather, int time) {
	GAMEPLAY::_SET_WEATHER_TYPE_OVER_TIME(weather, time);
}