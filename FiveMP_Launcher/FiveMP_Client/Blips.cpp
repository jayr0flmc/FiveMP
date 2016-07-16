#include "stdafx.h"

void CreateBlip(int blipID, int locationType, float x, float y, float z, int attachID, int color, int sprite, char* name)
{
	//Searching for empty blip place
	int clientblipid = -1;
	for (int i = 0; i < 100; i++) {
		if (!blipData[i].used) {
			clientblipid = i;
			break;
		}
	}
	if (clientblipid == -1) { 
		std::cout << "Server requested to create blip, but blip limit was exceeded" << std::endl;
		return;
	}

	blipData[clientblipid].used = true;
	blipData[clientblipid].serverID = blipID;

	switch (locationType) {
		case 0: {
			blipData[clientblipid].blip = UI::ADD_BLIP_FOR_COORD(x, y, z);
			break;
		}
		case 1: {
			int vehicleid = -1;
			for (int i = 0; i < 100; i++) {
				if (attachID == vehicleData[i].vehicleid) {
					vehicleid = vehicleData[i].vehicleVehicle;
					break;
				}
			}
			if (vehicleid == -1) { return; }

			blipData[clientblipid].blip = UI::ADD_BLIP_FOR_ENTITY(vehicleid);
			break;
		}
		case 2: {
			if (attachID != LocalPlayer->playerID) {
				blipData[clientblipid].blip = UI::ADD_BLIP_FOR_ENTITY(playerData[attachID].pedPed);
			}
			else {
				blipData[clientblipid].blip = UI::ADD_BLIP_FOR_ENTITY(LocalPlayer->playerPed);
			}
			break;
		}
	}

	UI::SET_BLIP_AS_FRIENDLY(blipData[clientblipid].blip, true);
	UI::SET_BLIP_SPRITE(blipData[clientblipid].blip, sprite);
	UI::SET_BLIP_COLOUR(blipData[clientblipid].blip, color);
	UI::SET_BLIP_SCALE(blipData[clientblipid].blip, 1.0f);
	UI::BEGIN_TEXT_COMMAND_SET_BLIP_NAME("STRING");
	UI::_ADD_TEXT_COMPONENT_STRING3(name);
	UI::END_TEXT_COMMAND_SET_BLIP_NAME(blipData[clientblipid].blip);
}
