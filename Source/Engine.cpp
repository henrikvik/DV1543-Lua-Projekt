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
	for (Blob * blob : blobs)
	{
		delete blob;
	}
}

void Engine::start()
{
	sf::Clock clock;

	while (window.isOpen())
	{
		pollEvents();
		update(clock.restart());

		window.clear(sf::Color(245,245,245));
		window.draw(*this);
		window.display();
	}
}

void Engine::addBlob(sf::Color color, const sf::Vector2f & position, float radius, const char * luaScript)
{
	Blob * blob = new Blob(color, position, radius, luaScript);
	LuaState * lua = blob->getLuaState();

	lua->push(Engine::lua_getInputDirection, lua)
		.setGlobal("getInputDirection");

	lua->push(Engine::lua_getClosestBlob, lua, blob, &blobs)
		.setGlobal("getClosestBlob");

	lua->push(Engine::lua_addBlob, lua, this)
		.setGlobal("addBlob");

	blobs.push_back(blob);
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
	size_t i, j, size = blobs.size();
	for (i = 0; i < size; i++)
	{
		blobs[i]->update(delta);

		for (j = i + 1; j < size; j++)
		{
			blobs[i]->checkCollision(*blobs[j]);
		}
	}

	blobs.erase(std::remove_if(blobs.begin(), blobs.end(), [](Blob* blob) {
		return blob->getRadius() < 0;
	}), blobs.end());
}

void Engine::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	size_t size = blobs.size();
	for (size_t i = 0; i < size; i++)
	{
		target.draw(*blobs[i], states);
	}
}

int Engine::lua_addBlob(LuaState * lua, Engine * engine)
{
	// addBlob({r, g, b}, 
	const char * script;
	float x, y, radius;
	lua->pop(script, radius);

	lua->getField("x").pop(x);
	lua->getField("y").pop(y);
	lua->pop();

	int r, g, b;
	
	lua->getField("r").pop(r);
	lua->getField("g").pop(g);
	lua->getField("b").pop(b);
	lua->pop();


	engine->addBlob(sf::Color(r, g, b), { x, y }, radius, script);

	return 0;
}

int Engine::lua_getClosestBlob(LuaState * lua, Blob * blob, BlobList * blobs)
{
	sf::Vector2f from = blob->getPosition();

	float distance = INFINITY;
	Blob * closest = nullptr;

	for (Blob* blob : *blobs)
	{
		float testDistance = blob->getDistance(from);
		if (testDistance < distance)
		{
			distance = testDistance;
			closest = blob;
		}
	}
	sf::Vector2f pos = { 0,0 };
	float radius = 0;

	if (closest != nullptr)
	{
		pos = closest->getPosition();
		radius = closest->getRadius();
	}

	lua->push(pos.x, pos.y, radius);
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
