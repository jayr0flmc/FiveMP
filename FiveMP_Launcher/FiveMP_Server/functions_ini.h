#pragma once

int LoadINIFile(lua_State* state);
int CloseINIFile(lua_State* state);

//read
int ReadInteger(lua_State* state);
int ReadFloat(lua_State* state);
int ReadBoolean(lua_State* state);
int ReadString(lua_State* state);

//load
int WriteInteger(lua_State* state);
int WriteFloat(lua_State* state);
int WriteBoolean(lua_State* state);
int WriteString(lua_State* state);