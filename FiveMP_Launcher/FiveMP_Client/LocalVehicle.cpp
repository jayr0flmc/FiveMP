#include "stdafx.h"

#include "stdafx.h"

CLocalVehicle::CLocalVehicle()
{
	vehicleVehicle = PED::GET_VEHICLE_PED_IS_IN(LocalPlayer->playerPed, false);
}

CLocalVehicle::~CLocalVehicle()
{
}

Vector4 CLocalVehicle::GetQuaternion()
{
	Vector4 rotation;

	ENTITY::GET_ENTITY_QUATERNION(vehicleVehicle, &rotation.fX, &rotation.fY, &rotation.fZ, &rotation.fW);

	return rotation;
}

void CLocalVehicle::SendVehicleData()
{
	RakNet::BitStream VehicleBitStream_send;

	VehicleBitStream_send.Write((MessageID)ID_SEND_VEHICLE_DATA);

	VehicleBitStream_send.Write(LocalPlayer->GetVehicle());

	VehicleBitStream_send.Write(GetModel());
	VehicleBitStream_send.Write(GetHealth());

	VehicleBitStream_send.Write(GetCoords().x);
	VehicleBitStream_send.Write(GetCoords().y);
	VehicleBitStream_send.Write(GetCoords().z);

	VehicleBitStream_send.Write(GetHeading());
	VehicleBitStream_send.Write(GetQuaternion().fX);
	VehicleBitStream_send.Write(GetQuaternion().fY);
	VehicleBitStream_send.Write(GetQuaternion().fZ);
	VehicleBitStream_send.Write(GetQuaternion().fW);

	VehicleBitStream_send.Write(GetVelocity().x);
	VehicleBitStream_send.Write(GetVelocity().y);
	VehicleBitStream_send.Write(GetVelocity().z);

	VehicleBitStream_send.Write(time(0));

	NetworkManager->client->Send(&VehicleBitStream_send, MEDIUM_PRIORITY, RELIABLE_ORDERED, 0, RakNet::UNASSIGNED_SYSTEM_ADDRESS, true);
}