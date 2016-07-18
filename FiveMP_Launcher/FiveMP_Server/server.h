#pragma once

//Some server functions
void sv_KickPlayer(int playerid);

//Raknet
void sv_PlayerConnect(RakNet::BitStream *bitStream, RakNet::Packet *packet);
void sv_OnPlayerPickUpPickup(RakNet::BitStream *bitStream, RakNet::Packet *packet);