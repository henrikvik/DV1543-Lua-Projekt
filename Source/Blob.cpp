#include "Blob.h"
#include <SFML/Graphics/RenderTarget.hpp>


Blob::Blob(sf::Color color, float radius, const char * luaPath)
{
	shape.setFillColor(color);
	setRadius(radius);
	lua.loadOpenLibs();
	lua.dofile(luaPath);
}

Blob::~Blob()
{
}

void Blob::update(sf::Time & delta)
{
	lua.getGlobal("update");
	lua.push(delta.asSeconds());
	lua.call(1, 0);
}

bool Blob::checkCollision(Blob & other)
{
	float minDist = radius + other.radius;
	float distance = sqrt(
		pow(position.x - other.position.x, 2) + 
		pow(position.y - other.position.y, 2));

	return distance < minDist;
}

void Blob::onCollision(Blob & other)
{
}

void Blob::setRadius(float radius)
{
	this->radius = radius;
	shape.setRadius(radius);
	setPosition(position);
}

void Blob::setPosition(sf::Vector2f & position)
{
	this->position = position;
	shape.setPosition({
		position.x - radius, 
		position.y - radius
	});
}

float Blob::getRadius()
{
	return radius;
}

sf::Vector2f Blob::getPosition()
{
	return position;
}

void Blob::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(shape);
}
