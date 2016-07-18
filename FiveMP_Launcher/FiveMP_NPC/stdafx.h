#pragma once

#define WIN32_LEAN_AND_MEAN

// Windows Header Files:
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <intrin.h>
#include <string>
#include <map>
#include <string.h>
#include <vector>
#include <sstream>
#include <Psapi.h>
#include <iostream>
#include <fstream>
#include <timeapi.h>
#include <time.h>
#include <tlhelp32.h>
#include <math.h>
#include <iostream>
#include <future>
using namespace std;

#pragma comment(lib, "winmm.lib")

// RakNet
#include <MessageIdentifiers.h>
#include <RakPeerInterface.h>
#include <RakNetStatistics.h>
#include <RakNetTypes.h>
#include <BitStream.h>
#include <RakSleep.h>
#include <PacketLogger.h>
#include <Kbhit.h>
#include <Gets.h>
#include <WindowsIncludes.h>
#include <GetTime.h>
#include <RPC4Plugin.h>
using namespace RakNet;

// INI Reader
#include <IniWriter.h>
#include <IniReader.h>

// Client
#include "main.h"

// Modification (FiveMP)
#include "Config.h"

// Net
#include "NetworkManager.h"
#include "RPCManager.h"
#include "PlayerPool.h"

extern MODULEINFO	g_MainModuleInfo;

extern CNetworkManager	*NetworkManager;
extern CRPCManager		*RPCManager;
extern CConfig			*Config;