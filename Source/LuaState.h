#pragma once
#include <lua.hpp>

class LuaState
{
public:
	LuaState();
	~LuaState();
	
	void dofile(const char * filePath);

	template<class T>
	void push(int(T::*fun)(LuaState&));

	void pop(const char *& str);

private:
	lua_State * state;
	void assert(bool condition, const char * message);
	void assert_pcall(int err, const char * message);
};

template<class T>
void LuaState::push(int(T::*fun)(LuaState&))
{
	lua_CFunction wrapper = [](lua_State * l) -> int {
		LuaState * L = lua_touserdata(l, lua_upvalueindex(1));
		int(T::*fun)(LuaState&) = lua_touserdata(l, lua_upvalueindex(2));
		return fun(*L);
	};

	lua_pushlightuserdata(state, this);
	lua_pushlightuserdata(state, fun);
	lua_pushcclosure(state, wrapper, 2);
}