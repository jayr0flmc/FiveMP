#pragma once

struct playerPool {
	int playerid;							// Player/Client ID
	char playerusername[24];					// Player Username (socialclub)

	int pedHealth;							// Ped Health
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

	float lastone;
	clock_t tickssince;

	bool used = false;						// Whether the player slot is in use or not.
};
extern playerPool playerData[128];