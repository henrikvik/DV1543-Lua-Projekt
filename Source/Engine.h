#pragma once
#include <vector>
#include <map>
#include <SFML\Graphics\RenderWindow.hpp>
#include <SFML\System\Clock.hpp>
#include "GameState.h"
#include "PlayState.h"

class Engine
{
public:
	Engine();
	~Engine();

	void start();

private:
	sf::RenderWindow window;
	sf::View camera;

	PlayState playState;
	GameState * currentState;

	void pollEvents();
};

