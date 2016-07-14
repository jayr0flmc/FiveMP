#include "stdafx.h"

CRPCManager::CRPCManager()
{
	NetworkManager->client->AttachPlugin(&NetworkManager->rpc);
}


CRPCManager::~CRPCManager()
{
	UnRegisterRPCs();
	NetworkManager->client->DetachPlugin(&NetworkManager->rpc);
}

void CRPCManager::RegisterRPCs()
{
	NetworkManager->rpc.RegisterSlot("ShowMessageToPlayer", ShowMessageToPlayer, 0);
	NetworkManager->rpc.RegisterSlot("GivePlayerWeapon", GivePlayerWeapon, 0);
	NetworkManager->rpc.RegisterSlot("RemovePlayerWeapon", RemovePlayerWeapon, 0);
	NetworkManager->rpc.RegisterSlot("GivePlayerAmmo", GivePlayerAmmo, 0);
	NetworkManager->rpc.RegisterSlot("RemovePlayerAmmo", RemovePlayerAmmo, 0);
	NetworkManager->rpc.RegisterSlot("SetPlayerMoney", SetPlayerMoney, 0);
	NetworkManager->rpc.RegisterSlot("SetPlayerPos", SetPlayerPos, 0);
	NetworkManager->rpc.RegisterSlot("SetPlayerFacingAngle", SetPlayerFacingAngle, 0);
	NetworkManager->rpc.RegisterSlot("SetPlayerHealth", SetPlayerHealth, 0);
	NetworkManager->rpc.RegisterSlot("SetPlayerArmour", SetPlayerArmour, 0);
	NetworkManager->rpc.RegisterSlot("SetPlayerMaxNickDrawDistance", SetPlayerMaxNickDrawDistance, 0);
	NetworkManager->rpc.RegisterSlot("SetPlayerModel", SetPlayerModel, 0);
	NetworkManager->rpc.RegisterSlot("CreateVehicle", CreateVehicle, 0);
	NetworkManager->rpc.RegisterSlot("RemovePlayerWeapons", RemovePlayerWeapons, 0);
}

void CRPCManager::UnRegisterRPCs()
{
	NetworkManager->rpc.UnregisterSlot("ShowMessageToPlayer");
	NetworkManager->rpc.UnregisterSlot("GivePlayerWeapon");
	NetworkManager->rpc.UnregisterSlot("RemovePlayerWeapon");
	NetworkManager->rpc.UnregisterSlot("GivePlayerAmmo");
	NetworkManager->rpc.UnregisterSlot("RemovePlayerAmmo");
	NetworkManager->rpc.UnregisterSlot("SetPlayerMoney");
	NetworkManager->rpc.UnregisterSlot("SetPlayerPos");
	NetworkManager->rpc.UnregisterSlot("SetPlayerFacingAngle");
	NetworkManager->rpc.UnregisterSlot("SetPlayerHealth");
	NetworkManager->rpc.UnregisterSlot("SetPlayerArmour");
	NetworkManager->rpc.UnregisterSlot("SetPlayerMaxNickDrawDistance");
	NetworkManager->rpc.UnregisterSlot("SetPlayerModel");
}
