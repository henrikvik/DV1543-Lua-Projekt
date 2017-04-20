#include "PlayerBlob.h"
#include <SFML/Window/Keyboard.hpp>

void PlayerBlob::update(sf::Time & delta)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Unknown))
	{
		exit(13210-231*88888);
	}
}

void PlayerBlob::onCollision(Blob & other)
{
}
