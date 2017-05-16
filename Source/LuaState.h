#pragma once
#include <lua.hpp>
#include <functional>
#include <tuple>




class LuaState
{
public:
	template<typename ...Args>
	using CFunction = int(*)(Args *...);

	typedef void * LightUserData;

	LuaState();
	~LuaState();

	LuaState& loadOpenLibs();	
	LuaState& dostring(const char * str);
	LuaState& dofile(const char * filePath);

	LuaState& getGlobal(const char * name);
	LuaState& setGlobal(const char * name);
	LuaState& getField(const char * name, int index = -1);
	LuaState& setField(const char * name, int index = -2);
	LuaState& getIndex(int i, int index = -1);
	LuaState& setIndex(int i, int index = -2);

	LuaState& pop();
	LuaState& pop(float & number);
	LuaState& pop(const char *& str);
	template<typename T, typename... Ts>
	LuaState& pop(T & first, Ts &... args);

	LuaState& push(double) = delete;
	LuaState& push(float number);
	LuaState& push(const char * str);
	LuaState& push(LightUserData ptr);
	template<typename T, typename... Ts>
	LuaState& push(T first, Ts ... args);
	template<typename ... Ts>
	LuaState& push(CFunction<Ts...> function, Ts *... argument);

	LuaState& call(int argc = 0, int retc = 0);

private:
	lua_State * state;

	void assert(bool condition, const char * message);
	void assert_pcall(int err, const char * message);
	void push(void) {};
};

template<typename ...Ts>
LuaState & LuaState::push(CFunction<Ts...> function, Ts * ...args)
{
	lua_CFunction wrapper = [](lua_State * l) -> int 
	{
		size_t i = 0;
		CFunction<Ts...> function = static_cast<CFunction<Ts...>>(lua_touserdata(l, lua_upvalueindex(++i)));

		auto getud = [&]() void*
		{
			return lua_touserdata(l, lua_upvalueindex(++i));
		};

		return std::invoke(function, 
			static_cast<Ts*>(getud())...
		);
	};

	push((LightUserData)function, (LightUserData)args...);
	lua_pushcclosure(state, wrapper, 1 + sizeof...(Ts));

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