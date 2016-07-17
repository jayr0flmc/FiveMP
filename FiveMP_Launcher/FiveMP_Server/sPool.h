#pragma once

typedef DWORD Hash;

class UserPool
{
public:
	int UserAmount;

	int AddToUserPool(char *username, RakNet::RakNetGUID guid);
	void RemoveFromUserPool(RakNet::RakNetGUID guid);
	
	int GetPlayerID(RakNet::RakNetGUID guid);
	const char *GetPlayerUsername(RakNet::RakNetGUID guid);
	RakNet::RakNetGUID GetPlayerGUID(char *username);
	RakNet::RakNetGUID GetPlayerGUIDfromId(int playerid);
};

class SpawnPointPool
{
public:
	int AddToSpawnPool(float x, float y, float z);
	void RemoveFromSpawnPool(int spawnid);
};

class VehiclePool
{
public:
	int VehicleAmount;

	int AddToVehiclePool(const char *modelname, float x, float y, float z, float heading, int color1, int color2, bool respawn, int respawndelay);
	void RemoveFromVehiclePool(int id);
};

struct playerPool {
	int playerid;							// Player/Client ID
	std::string playerusername;				// Player Username (set from client config)
	RakNet::RakNetGUID playerguid;			// Player GUID (client side)
	bool isConnected = false;				// Isconnected

	int pedType;							// Ped Type
	Hash pedModel;							// PedModel in hash
	int pedHealth = 100;					// Ped Health
	int pedArmour;							// Ped Armour

	float x;								// Position X coord
	float y;								// Position Y coord
	float z;								// Position Z coord
	
	float r;								// Rotation (0-360)
	float rx;								// Rotation X coord
	float ry;								// Rotation Y coord
	float rz;								// Rotation Z coord
	float rw;								// Rotation W coord

	float v;								// Velocity
	float vx;								// Velocity X coord
	float vy;								// Velocity Y coord
	float vz;								// Velocity Z coord

	int vehicleid;							// Current vehicle the player is in.
	int vehicleseat;						// Current seat the player is in. (vehicle)

	int money = 0;							// Money
	int score = 0;							// Score

	float maxNickDistance = 50.0f;			// Max nick draw distance

	bool dead = false;						// Whether the player dead or not.
	bool used = false;						// Whether the player slot is in use or not.

	bool isDefaultBlipRemoved = false;		// Checks if default blip is removed.
};
extern playerPool playerData[100];

struct spawnPool {
	int spawnid;							// Point ID

	float x;								// Position X coord
	float y;								// Position Y coord
	float z;								// Position Z coord

	bool used = false;						// Whether the SpawnPoint slot is in use or not.
};
extern spawnPool spawnData[50];

struct vehiclePool {
	int vehicleid;							// Vehicle ID (server)
	
	const char *spawnvehicleModel;			// Vehicle Model in const char
	Hash vehicleModel;						// Vehicle Model in Hash
	int vehicleHealth;						// Vehicle Health
	std::string vehiclePlate = std::string("FiveMP");				// Vehicle Lisence Plate (MAX 8 Chars)

	int vehicleColor1;						// Vehicle Color 1
	int vehicleColor2;						// Vehicle Color 2
	
	bool customcolor1Used = false;			// Wether or not this vehicle has a custom primary color (Mostly for OnPlayerConnect)
	bool customcolor2Used = false;			// Wether or not this vehicle has a custom secondary color (Mostly for OnPlayerConnect)
	int primarycr;							// Vehicle RColor 1
	int primarycg;							// Vehicle GColor 1
	int primarycb;							// Vehicle BColor 1
	int secondarycr;						// Vehicle RColor 2
	int secondarycg;						// Vehicle GColor 2
	int secondarycb;						// Vehicle BColor 2

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

	int playerid = -1;						// Player ID of who is inside.

	bool respawn;							// Whether the vehicle should respawn
	int respawndelay;						// Delay till vehicle respawns when unused (variable not used yet)

	bool used = false;						// Whether the vehicle slot is in use or not.
};
extern vehiclePool vehicleData[150];

struct blipPool {
	int locationType = 0;
	float x;
	float y;
	float z;
	int attachID;

	int color;
	int spriteid = 1;
	std::string name = std::string("No name");

	bool used = false;
};
extern blipPool blipData[100];