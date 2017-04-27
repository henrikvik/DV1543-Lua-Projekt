#include "PlayerBlob.h"
#include <SFML/Window/Keyboard.hpp>

PlayerBlob::PlayerBlob(sf::Color color, float radius, const char * luaPath)
	: Blob(color, radius)
{
	lua.loadOpenLibs().dofile(luaPath);
}

void PlayerBlob::update(sf::Time & delta)
{
	sf::Vector2f position;
	sf::Vector2f inputDir = getInputDirection();

	lua.getGlobal("inputDir")
		.push(inputDir.x).setField("x")
		.push(inputDir.y).setField("y")
	.pop();

	lua.getGlobal("update")
		.push(delta.asSeconds())
		.call(1, 0);

	lua.getGlobal("this")
		.getField("position")
			.getField("x").pop(position.x)
			.getField("y").pop(position.y)
		.pop()
	.pop();

	setPosition(position);
}

void PlayerBlob::onCollision(Blob & other)
{
}

sf::Vector2f PlayerBlob::getInputDirection()
{
	sf::Vector2f inputDir;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) inputDir.y--;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) inputDir.y++;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) inputDir.x--;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) inputDir.x++;

	float length = sqrt(pow(inputDir.x, 2) + pow(inputDir.y, 2));

	if (length > 0)
		inputDir /= length;

	return inputDir;
}
