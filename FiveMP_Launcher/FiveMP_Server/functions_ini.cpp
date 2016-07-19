#include "stdafx.h"

int LoadINIFile(lua_State * state)
{
	int args = lua_gettop(state);

	printf("LoadINIFile() was called with %d arguments:\n", args);

	std::string fileName = std::string(".//scriptfiles//") + std::string(lua_tostring(state, 1));

	//Creates file if it doesnt exist.
	std::ofstream file(fileName);
	file.close();

	int j = -1;
	for (int i = 0; i < 100; i++) {
		if (!iniData[i].used) {
			iniData[i].used = true;
			iniData[i].fileName = fileName;
			iniData[i].ini_Reader = new CIniReader((char*)fileName.c_str());
			iniData[i].ini_Writer = new CIniWriter((char*)fileName.c_str());
			j = i;
			break;
		}
	}
	if (j == -1) {
		lua_pushinteger(state, -1);
	}
	else {
		lua_pushinteger(state, j);
	}

	return 1;
}

int CloseINIFile(lua_State * state)
{
	int args = lua_gettop(state);

	printf("CloseINIFile() was called with %d arguments:\n", args);

	int file = lua_tointeger(state, 1);
	if (iniData[file].used) {
		iniData[file].used = false;
		delete iniData[file].ini_Reader;
		delete iniData[file].ini_Writer;
		iniData[file].ini_Reader = nullptr;
		iniData[file].ini_Writer = nullptr;
		iniData[file].fileName = std::string("");
	}

	return 0;
}

#define DEFAULT_SECTION "DATA"

int ReadInteger(lua_State * state)
{
	int args = lua_gettop(state);

	printf("ReadInteger() was called with %d arguments:\n", args);

	int file = lua_tointeger(state, 1);
	const char* key = lua_tostring(state, 2);
	if (iniData[file].used) {
		lua_pushinteger(state, iniData[file].ini_Reader->ReadInteger(DEFAULT_SECTION, (char*) key, 0));
	}
	else {
		lua_pushinteger(state, -1);
	}
	return 1;
}

int ReadFloat(lua_State * state)
{
	int args = lua_gettop(state);

	printf("ReadFloat() was called with %d arguments:\n", args);

	int file = lua_tointeger(state, 1);
	const char* key = lua_tostring(state, 2);
	if (iniData[file].used) {
		lua_pushnumber(state, iniData[file].ini_Reader->ReadFloat(DEFAULT_SECTION, (char*)key, 0.0f));
	}
	else {
		lua_pushnumber(state, -1.0f);
	}

	return 1;
}

int ReadBoolean(lua_State * state)
{
	int args = lua_gettop(state);

	printf("ReadBoolean() was called with %d arguments:\n", args);

	int file = lua_tointeger(state, 1);
	const char* key = lua_tostring(state, 2);
	if (iniData[file].used) {
		lua_pushboolean(state, iniData[file].ini_Reader->ReadBoolean(DEFAULT_SECTION, (char*)key, false));
	}
	else {
		lua_pushboolean(state, false);
	}
	return 1;
}

int ReadString(lua_State * state)
{
	int args = lua_gettop(state);

	printf("ReadBoolean() was called with %d arguments:\n", args);

	int file = lua_tointeger(state, 1);
	const char* key = lua_tostring(state, 2);
	if (iniData[file].used) {
		lua_pushstring(state, iniData[file].ini_Reader->ReadString(DEFAULT_SECTION, (char*)key, ""));
	}
	else {
		lua_pushstring(state, "");
	}
	return 1;
}

int WriteInteger(lua_State * state)
{
	int args = lua_gettop(state);

	printf("WriteInteger() was called with %d arguments:\n", args);

	int file = lua_tointeger(state, 1);
	const char* key = lua_tostring(state, 2);
	int value = lua_tointeger(state, 3);
	if (iniData[file].used) {
		iniData[file].ini_Writer->WriteInteger(DEFAULT_SECTION, (char*)key, value);
	}
	return 0;
}

int WriteFloat(lua_State * state)
{
	int args = lua_gettop(state);

	printf("WriteFloat() was called with %d arguments:\n", args);

	int file = lua_tointeger(state, 1);
	const char* key = lua_tostring(state, 2);
	float value = lua_tonumber(state, 3);
	if (iniData[file].used) {
		iniData[file].ini_Writer->WriteFloat(DEFAULT_SECTION, (char*)key, value);
	}
	return 0;
}

int WriteBoolean(lua_State * state)
{
	int args = lua_gettop(state);

	printf("WriteBoolean() was called with %d arguments:\n", args);

	int file = lua_tointeger(state, 1);
	const char* key = lua_tostring(state, 2);
	bool value = lua_toboolean(state, 3);
	if (iniData[file].used) {
		iniData[file].ini_Writer->WriteBoolean(DEFAULT_SECTION, (char*)key, value);
	}
	return 0;
}

int WriteString(lua_State * state)
{
	int args = lua_gettop(state);

	printf("WriteString() was called with %d arguments:\n", args);

	int file = lua_tointeger(state, 1);
	const char* key = lua_tostring(state, 2);
	const char* value = lua_tostring(state, 3);
	if (iniData[file].used) {
		iniData[file].ini_Writer->WriteString(DEFAULT_SECTION, (char*)key, (char*)value);
	}
	return 0;
}
