#include "stdafx.h"

playerPool playerData[128];

CNetworkManager *NetworkManager;
CRPCManager		*RPCManager;
CConfig			*Config;

HMODULE		FiveMP_Module;

void main() {
	Config		= new CConfig;

	Config->Read();

	if (!NetworkManager->Connect(Config->server_ipaddress, Config->server_port, Config->client_port)) {
		printf("rip, no connectioneeeee\n");
	}

	while (true)
	{
		if (NetworkManager->Listening) {
			NetworkManager->Pulse();

			if (NetworkManager->Connected) {
				if (!NetworkManager->Synchronized) {
					RakNet::BitStream requestid;

					char* playerUsername = Config->client_username;

					requestid.Write((MessageID)ID_REQUEST_SERVER_SYNC);
					requestid.Write(playerUsername);

					NetworkManager->client->Send(&requestid, HIGH_PRIORITY, RELIABLE_ORDERED, 0, RakNet::UNASSIGNED_SYSTEM_ADDRESS, true);
					NetworkManager->Synchronized = true;
				}
			}
		}
	}
}

unsigned char GetPacketIdentifier(RakNet::Packet *p)
{
	if (p == 0)
		return 255;

	if ((unsigned char)p->data[0] == ID_TIMESTAMP)
	{
		RakAssert(p->length > sizeof(RakNet::MessageID) + sizeof(RakNet::Time));
		return (unsigned char)p->data[sizeof(RakNet::MessageID) + sizeof(RakNet::Time)];
	}
	else
		return (unsigned char)p->data[0];
}
