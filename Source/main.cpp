#include "Engine.h"
#include <Windows.h>

#include "LuaState.h"
#include "PlayerBlob.h"
#include "AIBlob.h"



void main()
{
	Engine engine;

	engine.addBlob<PlayerBlob>(sf::Color::Blue, 50, "Assets/Lua/Player.lua");
	engine.addBlob<AIBlob>(sf::Color::Red, 50, "Assets/Lua/AI.lua");

	engine.start();

	system("pause");
}