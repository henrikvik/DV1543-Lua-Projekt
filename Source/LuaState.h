#pragma once
#include <lua.hpp>
#include <functional>
#include <tuple>

class LuaState
{
public:
	typedef int(*CppFunction)(LuaState&);

	LuaState();
	~LuaState();

	LuaState& loadOpenLibs();	
	LuaState& dostring(const char * str);
	LuaState& dofile(const char * filePath);
	LuaState& get(const char * name);
	LuaState& set(const char * name);

	LuaState& push(CppFunction function);
	LuaState& push(const char * str);
	LuaState& push(float number);

	LuaState& pop(const char *& str);
	LuaState& pop(float & number);

	LuaState& call(int argc, int retc);

	template<typename T, typename... Ts>
	LuaState& push(T first, Ts ... args);

	template<typename T, typename... Ts>
	LuaState& pop(T & first, Ts &... args);

private:
	lua_State * state;

	void assert(bool condition, const char * message);
	void assert_pcall(int err, const char * message);
};

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
