#include "LuaState.h"
#include <exception>

LuaState::LuaState()
{
	owner = true;
	state = luaL_newstate();
}

LuaState::LuaState(lua_State * l)
{
	owner = false;
	state = l;
}


LuaState::~LuaState()
{
	if (owner)
	{
		lua_close(state);
	}
}

void LuaState::loadOpenLibs()
{
	luaL_openlibs(state);
}

void LuaState::dostring(const char * str)
{
	assert_pcall(luaL_dostring(state, str), "dostring failed");
}

void LuaState::dofile(const char * filePath)
{
	assert_pcall(luaL_dofile(state, filePath), "dofile failed");
}

void LuaState::getGlobal(const char * name)
{
	lua_getglobal(state, name);
}

void LuaState::setGlobal(const char * name)
{
	lua_setglobal(state, name);
}

void LuaState::push(CppFunction function)
{
	static lua_CFunction wrapper = [&](lua_State * l) -> int {
		LuaState L(l);		
		CppFunction fun = reinterpret_cast<CppFunction>(lua_touserdata(l, lua_upvalueindex(1)));
		return fun(*L);
	};

	lua_pushlightuserdata(state, function);
	lua_pushcclosure(state, wrapper, 2);
}

void LuaState::push(const char * str)
{
	lua_pushstring(state, str);
}

void LuaState::push(float number)
{
	lua_pushnumber(state, number);
}

void LuaState::pop(const char *& str)
{
	assert(lua_isstring(state, -1), "top of stack is not string");
	str = lua_tostring(state, -1);
	lua_pop(state, 1);
}

void LuaState::call(int argc, int retc)
{
	assert_pcall(lua_pcall(state, argc, retc, NULL), "pcall failed");
}

void LuaState::assert(bool condition, const char * message)
{
	if (!condition)
	{
		printf("%s\n", message);
		exit(-2);
	}
}

void LuaState::assert_pcall(int pcall, const char * message)
{
	if (pcall != 0)
	{
		const char * error; pop(error);
		printf("%s: %s\n", message, error);
		system("pause");
		exit(-2);
	}
}
