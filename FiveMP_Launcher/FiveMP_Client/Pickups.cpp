#include "stdafx.h"

void CreatePickup(int pickupid, const char* modelid, float x, float y, float z, int interval)
{
	int clientpickupid = -1;
	for (int i = 0; i < 100; i++) {
		if (!pickupData[i].used) {
			clientpickupid = i;
			pickupData[i].used = true;
			pickupData[i].serverID = pickupid;
			break;
		}
	}
	if (clientpickupid == -1) { return; }

	pickupData[clientpickupid].model = GAMEPLAY::GET_HASH_KEY((char*) modelid);
	pickupData[clientpickupid].x = x;
	pickupData[clientpickupid].y = y;
	pickupData[clientpickupid].z = z;
	pickupData[clientpickupid].interval = interval;

	if (STREAMING::IS_MODEL_IN_CDIMAGE(pickupData[clientpickupid].model) && STREAMING::IS_MODEL_VALID(pickupData[clientpickupid].model))
		STREAMING::REQUEST_MODEL(pickupData[clientpickupid].model);
	while (!STREAMING::HAS_MODEL_LOADED(pickupData[clientpickupid].model))
		WAIT(0);

	//Creating pickup.
	pickupData[clientpickupid].pickup = OBJECT::CREATE_PICKUP(PickupTypeCustomScript, x, y, z, 0, 0, 0, pickupData[clientpickupid].model);

}

time_t lastclock = 0L;
void PickupUpdate()
{
	time_t time = clock();
	if (lastclock != 0L) {
		for (int i = 0; i < 100; i++) {
			if (pickupData[i].used) {

				if (pickupData[i].triggered) {
					pickupData[i].intv_clock -= time - lastclock;
				}

				if (OBJECT::DOES_PICKUP_EXIST(pickupData[i].pickup)) {
					//Basicly means if player picked it.
					if (!OBJECT::DOES_PICKUP_OBJECT_EXIST(pickupData[i].pickup)) {
						if (!pickupData[i].triggered) {
							RakNet::BitStream sOnPlayerPickupPickup;
							sOnPlayerPickupPickup.Write(pickupData[i].serverID);
							sOnPlayerPickupPickup.Write(LocalPlayer->playerID);
							NetworkManager->rpc.Signal("OnPlayerPickUpPickup", &sOnPlayerPickupPickup, HIGH_PRIORITY, RELIABLE_ORDERED, 0, UNASSIGNED_SYSTEM_ADDRESS, true, false);
							
							/*NOTE: Possible bug that on loading this code could be triggered but meh... xd If nobody won't notice this i wont care about it :D*/

							if (OBJECT::DOES_PICKUP_EXIST(pickupData[i].pickup)) {
								OBJECT::REMOVE_PICKUP(pickupData[i].pickup);
							}

							pickupData[i].triggered = true;
							pickupData[i].intv_clock = pickupData[i].interval;
						}
					}
				}
				else {
					if (pickupData[i].intv_clock <= 0 && pickupData[i].triggered) {
						pickupData[i].triggered = false;
						pickupData[i].intv_clock = 0;

						pickupData[i].pickup = OBJECT::CREATE_PICKUP(PickupTypeCustomScript, pickupData[i].x, pickupData[i].y, pickupData[i].z, 0, 0, 0, pickupData[i].model);
					}
				}
			}
		}
	}

	lastclock = time;
}

