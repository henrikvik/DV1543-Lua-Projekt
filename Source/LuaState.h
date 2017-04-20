#pragma once
#include <lua.hpp>
#include <functional>


class LuaState
{
public:
	typedef int(*CppFunction)(LuaState&);


	LuaState();
	~LuaState();

	void loadOpenLibs();
	
	void dostring(const char * str);
	void dofile(const char * filePath);

	void getGlobal(const char * name);
	void setGlobal(const char * name);



	void push(CppFunction function);
	void push(const char * str);
	void push(float number);

	void pop(const char *& str);

	void call(int argc, int retc);

private:
	lua_State * state;
	void assert(bool condition, const char * message);
	void assert_pcall(int err, const char * message);
};

