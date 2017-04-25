#pragma once
#include <lua.hpp>
#include <functional>
#include <tuple>



class LuaState
{
public:
	template<typename ...Args>
	using CFunction = int(*)(LuaState *, Args *...);

	LuaState();
	~LuaState();

	LuaState& loadOpenLibs();	
	LuaState& dostring(const char * str);
	LuaState& dofile(const char * filePath);
	LuaState& get(const char * name);
	LuaState& set(const char * name);

	LuaState& push(CFunction<> function);
	LuaState& push(const char * str);
	LuaState& push(float number);

	LuaState& pop(const char *& str);
	LuaState& pop(float & number);

	LuaState& call(int argc, int retc);

	template<typename T>
	LuaState& push(CFunction<T> function, T * argument);

	template<typename T, typename... Ts>
	LuaState& push(T first, Ts ... args);

	template<typename T, typename... Ts>
	LuaState& pop(T & first, Ts &... args);

private:
	lua_State * state;

	void assert(bool condition, const char * message);
	void assert_pcall(int err, const char * message);
};

template<typename T>
inline LuaState & LuaState::push(CFunction<T> function, T * argument)
{
	lua_CFunction wrapper = [](lua_State * l) -> int {
		LuaState   * luaState = static_cast<LuaState*>(lua_touserdata(l, lua_upvalueindex(1)));
		T          * argument = static_cast<T*>(lua_touserdata(l, lua_upvalueindex(2)));
		CFunction<T> function = static_cast<CFunction<T>>(lua_touserdata(l, lua_upvalueindex(3)));
		return function(luaState, instance);
	};

	lua_pushlightuserdata(state, this);
	lua_pushlightuserdata(state, argument);
	lua_pushlightuserdata(state, function);
	lua_pushcclosure(state, wrapper, 3);

	return *this;
}

template<typename T, typename... Ts>
LuaState & LuaState::push(T first, Ts ... args)
{
	push(first);
	push(args...);
	return *this;
}

template<typename T, typename ...Ts>
LuaState & LuaState::pop(T & first, Ts & ...args)
{
	pop(first);
	pop(args...);
	return *this;
}
