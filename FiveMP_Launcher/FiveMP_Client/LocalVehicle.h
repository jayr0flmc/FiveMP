#pragma once
class CLocalVehicle
{
public:
	Vehicle	vehicleVehicle;

	CLocalVehicle();
	~CLocalVehicle();

	Hash	GetModel() { return ENTITY::GET_ENTITY_MODEL(vehicleVehicle); };
	Vector3 GetCoords() { return ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(vehicleVehicle, 0.0, 0.0, -1.0f); };
	Vector3 GetVelocity() { return ENTITY::GET_ENTITY_VELOCITY(vehicleVehicle); };
	Vector4 GetQuaternion();
	int		GetHealth() { return ENTITY::GET_ENTITY_HEALTH(vehicleVehicle); };
	float	GetHeading() { return ENTITY::GET_ENTITY_HEADING(vehicleVehicle); };

	void	SetPos(float x, float y, float z) { ENTITY::SET_ENTITY_COORDS(vehicleVehicle, x, y, z, false, false, false, false); };
	void	SetHeading(float heading) { ENTITY::SET_ENTITY_HEADING(vehicleVehicle, heading); };

	void	SetHealth(int health) { ENTITY::SET_ENTITY_HEALTH(vehicleVehicle, health + 100); };

	void	SendVehicleData();
};
