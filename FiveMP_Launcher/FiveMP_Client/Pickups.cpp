#include "stdafx.h"

void CreatePickup(int pickupid, const char* modelid, float x, float y, float z)
{
	int clientpickupid = -1;
	for (int i = 0; i < 100; i++) {
		if (!pickupData[i].used) {
			clientpickupid = i;
			pickupData[i].used = true;
			pickupData[i].serverID = i;
			break;
		}
	}
	if (clientpickupid == -1) { return; }

	Hash model = GAMEPLAY::GET_HASH_KEY((char*) modelid);

	if (STREAMING::IS_MODEL_IN_CDIMAGE(model) && STREAMING::IS_MODEL_VALID(model))
		STREAMING::REQUEST_MODEL(model);
	while (!STREAMING::HAS_MODEL_LOADED(model))
		WAIT(0);

	std::cout << "I'm creating pickup" << std::endl;

	//Creating pickup.
	pickupData[clientpickupid].pickup = OBJECT::CREATE_PICKUP(PickupTypeCustomScript, x, y, z, 0, 0, 0, model);

}