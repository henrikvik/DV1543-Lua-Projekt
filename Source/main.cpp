#include "Engine.h"
#include <Windows.h>

#include "LuaState.h"


class A
{
public:
	int i = 0;
	int inc()
	{
		return i++;
	}
};

int l_test(LuaState * l, A * a)
{
	l->push(float(a->inc()));
	return 1;
}

void main()
{
	Engine game;

	game.addBlob(
		sf::Color::Red, 
		sf::Vector2f(0,0), 
		50, 
		"Assets/Lua/AI.lua" );

	game.addBlob(
		sf::Color::Blue,
		sf::Vector2f(-150, 0),
		60,
		"Assets/Lua/Player.lua");

	game.start();
}