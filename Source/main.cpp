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
	//Engine game;

	//game.addBlob(std::make_unique<Blob>( 
	//	sf::Color::Red, 
	//	sf::Vector2f(), 
	//	50, 
	//	"Assets/Lua/AI.lua" ));

	//game.addBlob(std::make_unique<Blob>(
	//	sf::Color::Blue,
	//	sf::Vector2f(-150, 0),
	//	60,
	//	"Assets/Lua/Player.lua"));

	//game.start();

	A a;
	LuaState l;
	l.loadOpenLibs();

	l.push(l_test, &l, &a);
	l.setGlobal("test");
	l.dostring("print(test())");
	l.dostring("print(test())");
	l.dostring("print(test())");
	l.dostring("print(test())");
	l.dostring("print(test())");
	l.dostring("print(test())");
}