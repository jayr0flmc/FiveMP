#pragma once
class CASIManager
{
public:
	CASIManager();
	~CASIManager();
	void Request();

	RakNet::SystemAddress sysAddrZero;
};