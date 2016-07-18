#include "stdafx.h"

SASIManager::SASIManager()
{
	NetworkManager->server->AttachPlugin(&NetworkManager->directoryDeltaTransfer);
	NetworkManager->server->AttachPlugin(&NetworkManager->fileListTransfer);
	NetworkManager->directoryDeltaTransfer.SetFileListTransferPlugin(&NetworkManager->fileListTransfer);

	NetworkManager->directoryDeltaTransfer.SetApplicationDirectory(".//");
	NetworkManager->directoryDeltaTransfer.AddUploadsFromSubdirectory("clientplugins");
	printf("%i files for upload.\n", NetworkManager->directoryDeltaTransfer.GetNumberOfFilesForUpload());
}


SASIManager::~SASIManager()
{
	NetworkManager->server->DetachPlugin(&NetworkManager->directoryDeltaTransfer);
	NetworkManager->server->DetachPlugin(&NetworkManager->fileListTransfer);
}
