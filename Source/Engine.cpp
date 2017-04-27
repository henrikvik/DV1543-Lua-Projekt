#include "Engine.h"
#include <SFML\Window\Event.hpp>
#include "AIBlob.h"
#include "PlayerBlob.h"

Engine::Engine()
{
	sf::VideoMode mode(800, 600);
	window.create(mode, "Lua Projekt", sf::Style::Close);

	camera.setCenter({ 0,0 });
	camera.setSize({ 800, 600 });

	window.setView(camera);
}


Engine::~Engine()
{
}


void Engine::start()
{
	sf::Clock clock;

	while (window.isOpen())
	{
		pollEvents();
		update(clock.restart());

		window.clear();
		window.draw(*this);
		window.display();
	}
}


void Engine::pollEvents()
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			window.close();
			break;
		}
	}
}

void Engine::update(sf::Time & delta)
{
	size_t size = blobs.size();
	for (size_t i = 0; i < size; i++)
	{
		blobs[i]->update(delta);

		for (size_t j = i + 1; j < size; j++)
		{ 
			if (blobs[i]->checkCollision(*blobs[j]))
			{	blobs[i]->onCollision(*blobs[j]);  }
		}
	}
}

void Engine::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	size_t size = blobs.size();
	for (size_t i = 0; i < size; i++)
	{
		target.draw(*blobs[i], states);
	}
}
