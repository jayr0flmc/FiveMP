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
	
}

void CRPCManager::UnRegisterRPCs()
{
	
}
