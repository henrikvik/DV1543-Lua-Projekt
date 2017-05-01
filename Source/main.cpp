#include "Engine.h"
#include <Windows.h>
#include <iostream>

#include "LuaState.h"

class Class
{
public:
	int i = 0;
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

	int i = 0;
	lua.push(fun, &c);
	lua.setGlobal("fun");
	lua.dostring("fun();fun();fun();fun()");


	system("pause");
}