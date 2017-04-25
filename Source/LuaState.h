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

	template<class Class>
	LuaState& push(Class * instance, CFunction<Class> function);

	template<typename T, typename... Ts>
	LuaState& push(T first, Ts ... args);

	template<typename T, typename... Ts>
	LuaState& pop(T & first, Ts &... args);

private:
	lua_State * state;

	void assert(bool condition, const char * message);
	void assert_pcall(int err, const char * message);
};

template<class Class>
inline LuaState & LuaState::push(Class * instance, CFunction<Class> function)
{
	lua_CFunction wrapper = [](lua_State * l) -> int {
		LuaState       * luaState = static_cast<LuaState*>(lua_touserdata(l, lua_upvalueindex(1)));
		Class          * instance = static_cast<Class*>(lua_touserdata(l, lua_upvalueindex(2)));
		CFunction<Class> function = static_cast<CFunction<Class>>(lua_touserdata(l, lua_upvalueindex(3)));
		return function(luaState, instance);
	};

	lua_pushlightuserdata(state, this);
	lua_pushlightuserdata(state, instance);
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
