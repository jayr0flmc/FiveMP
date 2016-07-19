#pragma once

struct playerPool {
	int playerid;							// Player/Client ID
	char playerusername[24];				// Player Username (socialclub)

	Ped pedPed;								// Used to spawn the ped and such.
	Blip pedBlip;
	Hash pedModel;							// PedModel in hash
	int pedHealth;							// Ped Health
	int pedArmour;							// Ped Armour
	int pedType;							// Ped Type

	float x;								// Position X coord
	float y;								// Position Y coord
	float z;								// Position Z coord

	float oldx;
	float oldy;
	float oldz;
	
	float r;								// Rotation (0-360)
	float rx;								// Rotation X coord
	float ry;								// Rotation Y coord
	float rz;								// Rotation Z coord
	float rw;								// Rotation W coord

	float v;								// Velocity
	float vx;								// Velocity X coord
	float vy;								// Velocity Y coord
	float vz;								// Velocity Z coord

	float screen_x;							// 2D X coord
	float screen_y;							// 2D Y coord

	int vehicleid = -1;						// Current vehicle the player is in.
	int vehicleseat = 0;					// Current seat the player is in. (vehicle)

	float lastone;
	clock_t tickssince;

	bool isDefaultBlipRemoved = false;
	bool used = false;						// Whether the player slot is in use or not.
};
extern playerPool playerData[150];

struct vehiclePool {
	int vehicleid;							// Vehicle ID (server)
	Vehicle localvehicleid;					// Vehicle ID (client)

	Vehicle vehicleVehicle;					// Used to spawn the vehicle and such.
	Blip vehicleBlip;						// Vehicle Blip
	Hash vehicleModel;						// Vehicle Model in Hash
	int vehicleHealth;						// Vehicle Health

	int vehicleColor1;						// Vehicle Color 1
	int vehicleColor2;						// Vehicle Color 2

	float oldx;
	float oldy;
	float oldz;

	float x;								// Position X coord
	float y;								// Position Y coord
	float z;								// Position Z coord

	float r;								// Rotation (0-360)
	float rx;								// Rotation X coord
	float ry;								// Rotation Y coord
	float rz;								// Rotation Z coord
	float rw;								// Rotation W coord

	float vx;								// Velocity X coord
	float vy;								// Velocity Y coord
	float vz;								// Velocity Z coord

	bool respawn;							// Whether the vehicle should respawn
	int respawndelay;						// Delay till vehicle respawns when unused (variable not used yet)

	float screen_x;							// 2D X coord
	float screen_y;							// 2D Y coord

	int playerid = -1;						// Player ID of who is inside

	clock_t tickssince;

	bool used = false;						// Whether the vehicle slot is in use or not.
};
extern vehiclePool vehicleData[125];

struct blipPool {
	int serverID;
	Blip blip;

	bool used = false;
};
extern blipPool blipData[100];

struct chatMessages {
	char message[128] = "";
};
extern chatMessages chatData[100];

struct pickupPool {
	int serverID;
	Pickup pickup;

	Hash model;
	float x;
	float y;
	float z;
	int interval;
	long intv_clock;


	bool used = false;
	bool triggered = false;
};
extern pickupPool pickupData[100];
