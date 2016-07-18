#include "stdafx.h"

bool iscomplete = false;

class TestCB : public RakNet::FileListTransferCBInterface
{
public:
	bool OnFile(
		OnFileStruct *onFileStruct)
	{
		assert(onFileStruct->byteLengthOfThisFile >= onFileStruct->bytesDownloadedForThisFile);
		printf("%i. (100%%) %i/%i %s %ib / %ib\n", onFileStruct->setID, onFileStruct->fileIndex + 1, onFileStruct->numberOfFilesInThisSet, onFileStruct->fileName, onFileStruct->byteLengthOfThisFile, onFileStruct->byteLengthOfThisSet);

		// Return true to have RakNet delete the memory allocated to hold this file.
		// False if you hold onto the memory, and plan to delete it yourself later
		return true;
	}

	virtual void OnFileProgress(FileProgressStruct *fps)
	{
		assert(fps->onFileStruct->byteLengthOfThisFile >= fps->onFileStruct->bytesDownloadedForThisFile);
		printf("%i (%i%%) %i/%i %s %ib / %ib\n", fps->onFileStruct->setID, (int)(100.0*(double)fps->partCount / (double)fps->partTotal),
			fps->onFileStruct->fileIndex + 1,
			fps->onFileStruct->numberOfFilesInThisSet,
			fps->onFileStruct->fileName,
			fps->onFileStruct->byteLengthOfThisFile,
			fps->onFileStruct->byteLengthOfThisSet,
			fps->firstDataChunk);
	}

	virtual bool OnDownloadComplete(DownloadCompleteStruct *dcs)
	{
		printf("Download complete.\n");
		iscomplete = true;

		// Returning false automatically deallocates the automatically allocated handler that was created by DirectoryDeltaTransfer
		return false;
	}

} transferCallback;


CASIManager::CASIManager()
{
	NetworkManager->client->AttachPlugin(&NetworkManager->directoryDeltaTransfer);
	NetworkManager->client->AttachPlugin(&NetworkManager->fileListTransfer);

	NetworkManager->directoryDeltaTransfer.SetApplicationDirectory(".//");
	NetworkManager->directoryDeltaTransfer.SetFileListTransferPlugin(&NetworkManager->fileListTransfer);
}


CASIManager::~CASIManager()
{
	NetworkManager->client->DetachPlugin(&NetworkManager->directoryDeltaTransfer);
	NetworkManager->client->DetachPlugin(&NetworkManager->fileListTransfer);
}

void CASIManager::Request()
{
	char subdir[256] = "";
	char outputSubdir[256] = "";

	unsigned short setId;
	while (iscomplete == false) {
		setId = NetworkManager->directoryDeltaTransfer.DownloadFromSubdirectory(subdir, outputSubdir, true, RakNet::UNASSIGNED_SYSTEM_ADDRESS, &transferCallback, HIGH_PRIORITY, 0, 0);
		if (setId == (unsigned short)-1) {
			printf("Download failed.  Host unreachable.\n");
		}
		else
		{
			printf("Downloading set %i\n", setId);
		}
		WAIT(0);
	}
}