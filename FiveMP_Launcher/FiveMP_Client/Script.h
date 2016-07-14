#pragma once

void ShowMessageToPlayer(RakNet::BitStream *bitStream, RakNet::Packet *packet);
void GivePlayerWeapon(RakNet::BitStream *bitStream, RakNet::Packet *packet);
void RemovePlayerWeapon(RakNet::BitStream *bitStream, RakNet::Packet *packet);
void RemoveAllPlayerWeapons(RakNet::BitStream *bitStream, RakNet::Packet *packet);
void GivePlayerAmmo(RakNet::BitStream *bitStream, RakNet::Packet *packet);
void RemovePlayerAmmo(RakNet::BitStream *bitStream, RakNet::Packet *packet);
void SetPlayerMoney(RakNet::BitStream *bitStream, RakNet::Packet *packet);
void SetPlayerPos(RakNet::BitStream *bitStream, RakNet::Packet *packet);
void SetPlayerFacingAngle(RakNet::BitStream *bitStream, RakNet::Packet *packet);
void SetPlayerHealth(RakNet::BitStream *bitStream, RakNet::Packet *packet);
void SetPlayerArmour(RakNet::BitStream *bitStream, RakNet::Packet *packet);
void SetPlayerMaxNickDrawDistance(RakNet::BitStream *bitStream, RakNet::Packet *packet);
void SetPlayerModel(RakNet::BitStream *bitStream, RakNet::Packet *packet);
void CreateVehicle(RakNet::BitStream *bitStream, RakNet::Packet *packet);
void SetPedComponentVariation(RakNet::BitStream *bitStream, RakNet::Packet *packet);
void ShowBlipForPlayer(RakNet::BitStream *bitStream, RakNet::Packet *packet);
void HideBlipFromPlayer(RakNet::BitStream *bitStream, RakNet::Packet *packet);