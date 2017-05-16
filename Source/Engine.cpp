#include "Engine.h"
#include <SFML\Window\Event.hpp>

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

void Engine::addBlob(std::unique_ptr<Blob>& blob)
{
	LuaState * lua = blob->getLuaState();

	lua->push(Engine::lua_getInputDirection, lua)
		.setGlobal("getInputDirection");

	lua->push(Engine::lua_getClosestBlob, lua, blob.get())//, &blobs)
		.setGlobal("getClosestBlob");

	blobs.push_back(std::move(blob));
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
			blobs[i]->checkCollision(*blobs[j]);
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

int Engine::lua_getClosestBlob(LuaState * lua, Blob * blob)//, std::vector<std::unique_ptr<Blob>> * blobs)
{
	//sf::Vector2f from = blob->getPosition();

	//float distance = INFINITY;
	//Blob * closest = nullptr;

	//for (size_t i = 0, size = blobs->size(); i < size; i++)
	//{
	//	float testDistance = blobs->at(i)->getDistance(from);
	//	if (testDistance < distance)
	//	{
	//		distance = testDistance;
	//		closest = blobs->at(i).get();
	//	}
	//}

	//sf::Vector2f pos = closest->getPosition();
	//float radius = closest->getRadius();

	//lua->push(pos.x, pos.y, radius);
	lua->push(1.0f, 2.0f, 3.0f);
	return 3;
}

int Engine::lua_getInputDirection(LuaState * lua)
{
	sf::Vector2f inputDir;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) inputDir.y--;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) inputDir.y++;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) inputDir.x--;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) inputDir.x++;

	float length = sqrt(pow(inputDir.x, 2) + pow(inputDir.y, 2));

	if (length > 0)
	{
		inputDir /= length;
	}

	lua->push(inputDir.x, inputDir.y);
	return 2;
}
