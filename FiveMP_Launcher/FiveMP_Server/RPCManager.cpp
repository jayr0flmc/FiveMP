#include "stdafx.h"

SRPCManager::SRPCManager()
{
	NetworkManager->server->AttachPlugin(&NetworkManager->rpc);
}


SRPCManager::~SRPCManager()
{
	UnRegisterRPCs();
	NetworkManager->server->DetachPlugin(&NetworkManager->rpc);
}

void SRPCManager::RegisterRPCs()
{
	NetworkManager->rpc.RegisterSlot("PlayerConnect", sv_PlayerConnect, 0);
}

void SRPCManager::UnRegisterRPCs()
{
	NetworkManager->rpc.UnregisterSlot("PlayerConnect");
}
