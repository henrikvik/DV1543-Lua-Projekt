#include "Blob.h"
#include <SFML/Graphics/RenderTarget.hpp>

size_t Blob::UID_BASE = 0;

Blob::Blob(sf::Color color, sf::Vector2f & position, float radius, const char * luaScript)
	: uid(UID_BASE++)
{
	lua.loadOpenLibs().dofile(luaScript);

	this->position = position;
	this->radius = radius;

	lua.getGlobal("this")
		.push(radius).setField("radius")
		.getField("position")
			.push(position.x).setField("x")
			.push(position.y).setField("y")
		.pop()
	.pop();

	shape.setFillColor(color);
	shape.setRadius(radius);
	shape.setPosition({
		position.x - radius, 
		position.y - radius });
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

	shape.setRadius(radius);
	shape.setPosition({
		position.x - radius,
		position.y - radius
	});
}

void Blob::checkCollision(Blob & other)
{
	float minDist = radius + other.radius;
	float distance = sqrt(
		pow(position.x - other.position.x, 2) + 
		pow(position.y - other.position.y, 2));

	if (distance < minDist)
	{
		lua.getGlobal("onCollision")
			.push(other.radius)
			.push(distance)
		.call(2, 0);

		other.lua.getGlobal("onCollision")
			.push(radius)
			.push(distance)
		.call(2, 0);
	};
}

LuaState & Blob::getLuaState()
{
	return lua;
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