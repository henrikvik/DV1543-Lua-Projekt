#include <SFML\Graphics\RenderTarget.hpp>
#include <SFML\Window\Keyboard.hpp>
#include "PlayState.h"
#include "FileHandler.h"

PlayState::PlayState()
{
}

PlayState::~PlayState()
{
}

void PlayState::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	for (size_t i = 0, size = blobs.size(); i < size; i++)
	{
		target.draw(*blobs[i], states);
	}
}

void PlayState::update(float delta)
{
	for (size_t i = 0, j, size = blobs.size(); i < size; i++)
	{
		blobs[i]->update(delta);

		for (j = i + 1; j < size; j++)
		{
			blobs[i]->checkCollision(*blobs[j]);
		}
	}

	blobs.erase(
		std::remove_if(
			blobs.begin(), 
			blobs.end(), 
			[](Blob * blob) 
			{
				return blob->getRadius() <= 0.0f;
			}
		), 
		blobs.end()
	);
}

void PlayState::onEnter()
{
	addBlobs(FileHandler::readFromFile("Assets/Blobs.txt"));
}

void PlayState::onLeave()
{
	blobs.clear();
}

void PlayState::addBlob(sf::Color color, const sf::Vector2f & position, float radius, const char * luaScript)
{
	Blob * blob = new Blob(color, position, radius, luaScript);
	LuaState * lua = blob->getLuaState();

	lua->push(PlayState::lua_getInputDirection, lua)
		.setGlobal("getInputDirection");

	lua->push(PlayState::lua_getClosestBlob, lua, blob, &blobs)
		.setGlobal("getClosestBlob");

	lua->push(PlayState::lua_addBlob, lua, this)
		.setGlobal("addBlob");

	lua->push(PlayState::lua_quitGame, this)
		.setGlobal("quitGame");

	blobs.push_back(blob);
}

void PlayState::addBlobs(std::vector<Blob*>newBlobs)
{
	for each (Blob* blob in newBlobs)
	{
		LuaState * lua = blob->getLuaState();

	lua->push(PlayState::lua_getInputDirection, lua)
		.setGlobal("getInputDirection");

	lua->push(PlayState::lua_getClosestBlob, lua, blob, &blobs)
		.setGlobal("getClosestBlob");

	lua->push(PlayState::lua_addBlob, lua, this)
		.setGlobal("addBlob");

	lua->push(PlayState::lua_quitGame, this)
		.setGlobal("quitGame");

	blobs.push_back(blob);
	}
	
}

int PlayState::lua_quitGame(PlayState * state)
{
	state->pushEvent({ GameState::Event::QUIT });
	return 0;
}

int PlayState::lua_getClosestBlob(LuaState * lua, Blob * blob, BlobList * blobs)
{
	sf::Vector2f from = blob->getPosition();

	float distance = INFINITY;
	Blob * closest = nullptr;

	for (Blob * blob : *blobs)
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

int PlayState::lua_addBlob(LuaState * lua, PlayState *  state)
{
	// addBlob({r, g, b}, {x, y}, radius, script);
	const char * script;
	float radius, x, y;
	int r, g, b;

	lua->pop(script, radius);

	lua->getField("x").pop(x);
	lua->getField("y").pop(y);
	lua->pop();

	lua->getField("r").pop(r);
	lua->getField("g").pop(g);
	lua->getField("b").pop(b);
	lua->pop();

	state->addBlob(sf::Color(r, g, b), sf::Vector2f(x, y), radius, script);
	return 0;
}

int PlayState::lua_getInputDirection(LuaState * lua)
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
