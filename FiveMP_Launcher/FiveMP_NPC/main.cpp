#include "stdafx.h"

playerPool playerData[128];

CNetworkManager *NetworkManager;
CRPCManager		*RPCManager;
CASIManager		*ASIManager;
CConfig			*Config;

HMODULE		FiveMP_Module;

time_t timesince;

void main() {
	Config			= new CConfig;
	NetworkManager	= new CNetworkManager;
	RPCManager		= new CRPCManager;
	ASIManager		= new CASIManager;

	Config->Read();

	printf("\n%s joining with port: %s\n", Config->server_ipaddress, Config->server_port);

	if (!NetworkManager->Connect(Config->server_ipaddress, Config->server_port, Config->client_port)) {
		printf("not able to connect :(\n");
	}

	while (true)
	{
		if (NetworkManager->Listening) {

			NetworkManager->Pulse();

			if (NetworkManager->Connected) {
				if (!NetworkManager->Synchronized) {
					if (time(0) - timesince > 10) {

						RakNet::BitStream requestid;

						char* playerUsername = Config->client_username;

						requestid.Write((MessageID)ID_REQUEST_SERVER_SYNC);
						requestid.Write(playerUsername);

						NetworkManager->client->Send(&requestid, HIGH_PRIORITY, RELIABLE_ORDERED, 0, RakNet::UNASSIGNED_SYSTEM_ADDRESS, true);

						timesince = time(0);

						ASIManager->Request();
					}
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
