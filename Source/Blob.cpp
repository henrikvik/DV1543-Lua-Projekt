#include "Blob.h"
#include <SFML/Graphics/RenderTarget.hpp>


Blob::Blob(sf::Color color, float radius)
{
	shape.setFillColor(color);
	setRadius(radius);
}

Blob::~Blob()
{
}

void Blob::update(sf::Time & delta)
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
