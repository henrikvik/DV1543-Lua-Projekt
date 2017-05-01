#include "Engine.h"
#include <Windows.h>
#include <iostream>

#include "LuaState.h"

class Class
{
public:
	int i = 0;
	int fun()
	{
		printf("Hello World %d\n", i++);
		return 0;
	}
};


int fun(Class * c)
{
	printf("Hello World %d\n", c->i++);
	return 0;
}


void main()
{
	//Engine game;
	//game.run();

	LuaState lua;
	lua.loadOpenLibs();

	Class c;

	lua.push<LuaState::CFunction<Class>>([] (Class * c) {
		c->fun();
		return 0;
	}, &c);
	lua.setGlobal("fun");
	lua.dostring("fun();fun();fun();fun()");


	system("pause");
}