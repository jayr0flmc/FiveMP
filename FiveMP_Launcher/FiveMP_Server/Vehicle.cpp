#include "stdafx.h"

SVehicle::SVehicle()
{
}

SVehicle::~SVehicle()
{
}

void SVehicle::SpawnVehicles(int playerid)
{
	for (int i = 0; i < 100; i++) {
		if (vehicleData[i].used == true) {

			RakNet::RakString vehiclename = vehicleData[i].spawnvehicleModel;

			RakNet::BitStream sCreateVehicle;
			sCreateVehicle.Write(vehicleData[i].vehicleid);
			sCreateVehicle.Write(vehiclename);
			sCreateVehicle.Write(vehicleData[i].x);
			sCreateVehicle.Write(vehicleData[i].y);
			sCreateVehicle.Write(vehicleData[i].z);
			sCreateVehicle.Write(vehicleData[i].r);
			sCreateVehicle.Write(vehicleData[i].vehicleColor1);
			sCreateVehicle.Write(vehicleData[i].vehicleColor2);
			sCreateVehicle.Write(vehicleData[i].respawn);
			sCreateVehicle.Write(vehicleData[i].respawndelay);
			NetworkManager->rpc.Signal("CreateVehicle", &sCreateVehicle, HIGH_PRIORITY, RELIABLE_ORDERED, 0, netPool.GetPlayerGUIDfromId(playerid), false, false);

			if (vehicleData[i].customcolor1Used) {
				RakNet::BitStream sVehicleColor;
				sVehicleColor.Write(vehicleData[i].vehicleid);
				sVehicleColor.Write(1);
				sVehicleColor.Write(vehicleData[i].primarycr);
				sVehicleColor.Write(vehicleData[i].primarycg);
				sVehicleColor.Write(vehicleData[i].primarycb);
				NetworkManager->rpc.Signal("SetVehicleCustomColor", &sVehicleColor, HIGH_PRIORITY, RELIABLE_ORDERED, 0, netPool.GetPlayerGUIDfromId(playerid), false, false);
			}

			if (vehicleData[i].customcolor2Used) {
				RakNet::BitStream sVehicleColor;
				sVehicleColor.Write(vehicleData[i].vehicleid);
				sVehicleColor.Write(1);
				sVehicleColor.Write(vehicleData[i].secondarycr);
				sVehicleColor.Write(vehicleData[i].secondarycg);
				sVehicleColor.Write(vehicleData[i].secondarycb);
				NetworkManager->rpc.Signal("SetVehicleCustomColor", &sVehicleColor, HIGH_PRIORITY, RELIABLE_ORDERED, 0, netPool.GetPlayerGUIDfromId(playerid), false, false);
			}
			/*
			RakNet::RakString string;

			if (vehicleData[i].vehiclePlate.length == 0) {
				string = RakNet::RakString("FiveMP");
			}
			else {
				string = RakNet::RakString(vehicleData[i].vehiclePlate.c_str());
			}

			RakNet::BitStream sVehiclePlate;
			sVehiclePlate.Write(vehicleData[i].vehicleid);
			sVehiclePlate.Write(string);
			NetworkManager->rpc.Signal("SetVehicleNumberPlate", &sVehiclePlate, LOW_PRIORITY, RELIABLE_ORDERED, 0, netPool.GetPlayerGUIDfromId(playerid), false, false);
			*/
		}
	}
}
