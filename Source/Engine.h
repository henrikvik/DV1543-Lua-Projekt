#pragma once
#include <vector>
#include <map>
#include <SFML\Graphics\RenderWindow.hpp>
#include <SFML\System\Clock.hpp>
#include "GameState.h"
#include "PlayState.h"
#include "MenuState.h"
#include "EditorState.h"

class Engine
{
public:
	Engine();
	~Engine();

	void start();

private:
	sf::RenderWindow window;
	sf::View camera;

	MenuState menuState;
	PlayState playState;
	EditorState editorState;
	GameState * currentState;

	void pollEvents();
};

