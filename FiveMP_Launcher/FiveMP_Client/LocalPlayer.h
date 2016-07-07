#pragma once
class CLocalPlayer
{
public:
	Ped	playerPed;

	CLocalPlayer();
	~CLocalPlayer();

	Hash	GetModel() { return ENTITY::GET_ENTITY_MODEL(playerPed); };
	Vector3 GetCoords() { return ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(playerPed, 0.0, 0.0, 0.0); };
	Vector3 GetVelocity() { return ENTITY::GET_ENTITY_VELOCITY(playerPed); };
	int		GetType() { return PED::GET_PED_TYPE(playerPed); };
	int		GetHealth() { return ENTITY::GET_ENTITY_HEALTH(playerPed); };
	float	GetHeading() { return ENTITY::GET_ENTITY_HEADING(playerPed); };
};
