#include "LuaState.h"
#include <exception>

LuaState::LuaState()
{
	state = luaL_newstate();
	luaL_openlibs(state);
}


LuaState::~LuaState()
{
	lua_close(state);
}

void LuaState::dofile(const char * filePath)
{
	assert_pcall(luaL_dofile(state, filePath), "dofile failed");
}

void LuaState::pop(const char *& str)
{
	assert(lua_isstring(state, -1), "top of stack is not string");
	str = lua_tostring(state, -1);
	lua_pop(state, 1);
}

void LuaState::assert(bool condition, const char * message)
{
	if (!condition)
	{
		printf("%s\n", message);
		throw std::exception();
	}
}

void LuaState::assert_pcall(int pcall, const char * message)
{
	if (pcall != 0)
	{
		const char * error; pop(error);
		printf("%s: %s\n", message, error);
		throw std::exception();
	}
}
