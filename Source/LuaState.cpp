#include "LuaState.h"
#include <exception>

LuaState::LuaState()
{
	state = luaL_newstate();
}

LuaState::~LuaState()
{
	lua_close(state);
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

LuaState& LuaState::get(const char * name)
{
	lua_getglobal(state, name);
	return *this;
}

LuaState& LuaState::set(const char * name)
{
	lua_setglobal(state, name);
	return *this;
}

LuaState& LuaState::push(CFunction<> function)
{
	lua_CFunction wrapper = [](lua_State * l) -> int {
		LuaState  * luaState = static_cast<LuaState*>(lua_touserdata(l, lua_upvalueindex(1)));
		CFunction<> function = static_cast<CFunction<>>(lua_touserdata(l, lua_upvalueindex(2)));
		return function(luaState);
	};

	lua_pushlightuserdata(state, this);
	lua_pushlightuserdata(state, function);
	lua_pushcclosure(state, wrapper, 2);
	return *this;
}

LuaState& LuaState::push(const char * str)
{
	lua_pushstring(state, str);
	return *this;
}

LuaState& LuaState::push(float number)
{
	lua_pushnumber(state, number);
	return *this;
}

LuaState& LuaState::pop(const char *& str)
{
	assert(lua_isstring(state, -1), "top of stack is not string");
	str = lua_tostring(state, -1);
	lua_pop(state, 1);
	return *this;
}

LuaState& LuaState::pop(float & number)
{
	assert(lua_isnumber(state, -1), "top of stack is not a number");
	number = lua_tonumber(state, -1);
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
		throw std::exception(message);
	}
}

void LuaState::assert_pcall(int pcall, const char * message)
{
	if (pcall != 0)
	{
		const char * error; pop(error);
		printf("%s: %s\n", message, error);
		throw std::exception(message);
	}
}
