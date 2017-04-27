#pragma once
#include <SFML\Graphics\Drawable.hpp>
#include <SFML\Graphics\CircleShape.hpp>
#include <SFML\System\Time.hpp>

#include "LuaState.h"

class Blob : public sf::Drawable
{
public:
	Blob(sf::Color color, float radius, const char * lua);
	virtual ~Blob();

	virtual void update(sf::Time & delta);
	virtual void onCollision(Blob & other);

	void setRadius(float radius);
	void setPosition(sf::Vector2f & position);

	void move(sf::Vector2f delta);

	float getRadius();
	sf::Vector2f getPosition();

	bool checkCollision(Blob & other);

	// Inherited via Drawable
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override;
private:
	sf::CircleShape shape;
	sf::Vector2f position;
	float radius;

	LuaState lua;
};

