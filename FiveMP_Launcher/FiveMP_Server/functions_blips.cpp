#include "stdafx.h"

int CreateBlip(lua_State * state)
{
	int args = lua_gettop(state);

	printf("CreateBlip() was called with %d arguments.\n", args);

	

	return 1;
}
