#pragma once

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

typedef DWORD Hash;

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

	int money = 0;							// Money
	int score = 0;							// Score

	float maxNickDistance = 50.0f;			// Max nick draw distance

	bool dead = false;						// Whether the player dead or not.
	bool used = false;						// Whether the player slot is in use or not.
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