#include "LuaState.h"
#include <exception>

LuaState::LuaState()
{
	state = luaL_newstate();
}

LuaState::~LuaState()
{
	//lua_close(state);
}

LuaState& LuaState::loadOpenLibs()
{
	luaL_openlibs(state);
	return *this;
}

LuaState& LuaState::dostring(const char * str)
{
	assert_pcall(luaL_dostring(state, str), "dostring failed");
	return *this;
}

LuaState& LuaState::dofile(const char * filePath)
{
	assert_pcall(luaL_dofile(state, filePath), "dofile failed");
	return *this;
}

LuaState& LuaState::getGlobal(const char * name)
{
	lua_getglobal(state, name);
	return *this;
}

LuaState& LuaState::setGlobal(const char * name)
{
	lua_setglobal(state, name);
	return *this;
}

LuaState & LuaState::getField(const char * name, int index)
{
	lua_getfield(state, index, name);
	return *this;
}

LuaState & LuaState::setField(const char * name, int index)
{
	lua_setfield(state, index, name);
	return *this;
}

LuaState & LuaState::getIndex(int i, int index)
{
	lua_geti(state, index, i);
	return *this;
}

LuaState & LuaState::setIndex(int i, int index)
{
	lua_seti(state, index, i);
	return *this;
}

LuaState& LuaState::push(const char * str)
{
	lua_pushstring(state, str);
	return *this;
}

LuaState & LuaState::push(LightUserData ptr)
{
	lua_pushlightuserdata(state, ptr);
	return *this;
}

LuaState & LuaState::push(int number)
{
	lua_pushinteger(state, number);
	return *this;
}

LuaState& LuaState::push(float number)
{
	lua_pushnumber(state, number);
	return *this;
}

LuaState & LuaState::pop()
{
	lua_pop(state, 1);
	return *this;
}

LuaState & LuaState::pop(int & number)
{
	number = static_cast<int>(luaL_checkinteger(state, -1));
	lua_pop(state, 1);
	return *this;
}

LuaState& LuaState::pop(const char *& str)
{
	str = luaL_checkstring(state, -1);
	lua_pop(state, 1);
	return *this;
}

LuaState& LuaState::pop(float & number)
{
	number = static_cast<float>(luaL_checknumber(state, -1));
	lua_pop(state, 1);
	return *this;
}

LuaState& LuaState::call(int argc, int retc)
{
	assert_pcall(lua_pcall(state, argc, retc, NULL), "pcall failed");
	return *this;
}

void LuaState::assert(bool condition, const char * message)
{
	if (!condition)
	{
		printf("%s\n", message);
		system("pause");
		exit(-1);
	}
}

void LuaState::assert_pcall(int pcall, const char * message)
{
	if (pcall != 0)
	{
		const char * error; pop(error);
		printf("%s: %s\n", message, error);
		system("pause");
		exit(-1);
	}
}
