#include "Blob.h"
#include <SFML/Graphics/RenderTarget.hpp>

size_t Blob::UID_BASE = 0;

Blob::Blob(LuaState & lua, sf::Color color, float radius, const char * luaScript)
	: uid(UID_BASE++), lua(lua)
{

	shape.setFillColor(color);
	shape.setPosition({ -radius, -radius });
}

Blob::~Blob()
{
}

void Blob::update(sf::Time & delta)
{
	lua.getGlobal("update")
		.push(delta.asSeconds())
	.call(1, 0);

	lua.getGlobal("this")
		.getField("radius").pop(radius)
		.getField("position")
			.getField("x").pop(position.x)
			.getField("y").pop(position.y)
		.pop()
	.pop();

	shape.setPosition({
		position.x - radius,
		position.y - radius
	});
}

void Blob::onCollision(Blob & other)
{

}

bool Blob::checkCollision(Blob & other)
{
	float minDist = radius + other.radius;
	float distance = sqrt(
		pow(position.x - other.position.x, 2) + 
		pow(position.y - other.position.y, 2));

	return distance < minDist;
}

inline const float & Blob::getRadius()
{
	return radius;
}

inline const sf::Vector2f & Blob::getPosition()
{
	return position;
}

void Blob::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(shape);
}