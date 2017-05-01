#include "Engine.h"
#include <Windows.h>

#include "LuaState.h"



void main()
{
	Engine game;

	game.addBlob(std::make_unique<Blob>( 
		sf::Color::Red, 
		sf::Vector2f(), 
		50, 
		"Assets/Lua/AI.lua" ));

	game.addBlob(std::make_unique<Blob>(
		sf::Color::Blue,
		sf::Vector2f(-150, 0),
		60,
		"Assets/Lua/Player.lua"));

	game.start();
}