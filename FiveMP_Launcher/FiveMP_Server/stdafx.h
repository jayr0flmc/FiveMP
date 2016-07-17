#pragma once

#define WIN32_LEAN_AND_MEAN

// Windows Header Files:
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <intrin.h>
#include <string>
#include <vector>
#include <sstream>
#include <Psapi.h>
#include <iostream>
#include <fstream>
#include <time.h>
#include <direct.h>

#pragma comment(lib, "winmm.lib")

extern MODULEINFO g_MainModuleInfo;

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

// Modification
#include "Config.h"

// Netcode
#include "NetworkManager.h"
#include "RPCManager.h"

#include "sPool.h"

// INI Reader
#include "IniWriter.h"
#include "IniReader.h"

// Functions
#include "server.h"
#include "player.h"
#include "vehicle.h"
#include "world.h"

// Scripting (LUA)
#include <lua.hpp>

// Scripting (LUA-Functions)
#include "functions_main.h"
#include "functions_hud.h"
#include "functions_player.h"
#include "functions_blips.h"
#include "functions_vehicle.h"
#include "functions_pickups.h"

// Scripting (LUA-Callbacks)
#include "callbacks.h"

namespace {
	// Pools (net)
	class UserPool netPool;
	class SpawnPointPool spawnsPool;
	class VehiclePool vehiclesPool;
}

extern lua_State* sLUA;

extern SNetworkManager	*NetworkManager;
extern SRPCManager		*RPCManager;
extern SConfig			*Config;
extern SPlayer			*PlayerManager;
extern SVehicle			*VehicleManager;
extern SWorld			*WorldManager;