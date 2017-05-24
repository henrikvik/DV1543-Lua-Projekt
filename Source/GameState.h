#pragma once
#include <SFML\Graphics\Drawable.hpp>

class GameState :
	public sf::Drawable
{
public:
	virtual void update() = 0;
	virtual void onEnter() = 0;
	virtual void onLeave() = 0;
};

