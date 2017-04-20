#pragma once
#include <lua.hpp>
#include <functional>


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

private:
	lua_State * state;

	void assert(bool condition, const char * message);
	void assert_pcall(int err, const char * message);

	template<typename T, typename ... Ts>
	int count_args(T& t, Ts &... ts);
};

template<typename T, typename ...Ts>
inline int LuaState::count_args(T & t, Ts & ...ts)
{
	return 0;
}
