#include "Engine.h"
#include <SFML\Window\Event.hpp>

Engine::Engine()
	: menuState(window)
{
	sf::VideoMode mode(800, 600);
	window.create(mode, "Lua Projekt", sf::Style::Close);

	camera.setCenter({ 0,0 });
	camera.setSize({ 800, 600 });

	window.setView(camera);

	currentState = &menuState;
}

Engine::~Engine()
{

}

void Engine::start()
{
	sf::Clock clock;

	currentState->onEnter();
	while (window.isOpen())
	{
		pollEvents();
		currentState->update(clock.restart().asSeconds());
		window.clear(sf::Color(245,245,245));
		window.draw(*currentState);
		window.display();
	}
}

void Engine::pollEvents()
{
	sf::Event windowEvent;
	while (window.pollEvent(windowEvent))
	{
		switch (windowEvent.type)
		{
		case sf::Event::Closed:
			window.close();
			break;
		}
	}

	GameState::Event gameEvent;
	while (currentState->pollEvent(gameEvent))
	{
		switch (gameEvent.type)
		{
		case GameState::Event::QUIT:
			window.close();
			break;
		case GameState::Event::MENU:
			currentState->onLeave();
			currentState = &menuState;
			currentState->onEnter();
			break;
		case GameState::Event::PLAY:
			currentState->onLeave();
			currentState = &playState;
			currentState->onEnter();
			break;
		}
	}
}
