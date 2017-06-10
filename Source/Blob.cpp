#include "Blob.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include <sstream>

size_t Blob::UID_BASE = 0;

Blob::Blob(float lifeSpan, float growthRate, float moveSpeed, int colorRed, int colorGreen, int colorBlue, float radius, float x, float y, const std::string & script)
	: uid(UID_BASE++)
{
	lua.loadOpenLibs().dofile(script.c_str());
	this->script = script;

	this->position = { x, y };
	sf::Color color(colorRed, colorGreen, colorBlue);
	this->radius = radius;

	lua.getGlobal("this");
		lua.push(lifeSpan).setField("lifeSpan");
		lua.push(growthRate).setField("growthRate");
		lua.push(moveSpeed).setField("moveSpeed");
		lua.push(radius).setField("radius");
		lua.getField("position");
			lua.push(position.x).setField("x");
			lua.push(position.y).setField("y");
		lua.pop();
		lua.getField("color");
			lua.push((int)color.r).setField("r");
			lua.push((int)color.g).setField("g");
			lua.push((int)color.b).setField("b");
		lua.pop();
	lua.pop();

	shape.setFillColor(color);
	shape.setRadius(radius);
	shape.setPosition({
		position.x - radius,
		position.y - radius });
}

Blob::~Blob()
{
}

void Blob::update(float delta)
{
	lua.getGlobal("update")
		.push(delta)
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

LuaState * Blob::getLuaState()
{
	return &lua;
}

float Blob::getDistance(const sf::Vector2f & point)
{
	sf::Vector2f diff = point - position;
	return sqrt(pow(diff.x, 2) + pow(diff.y, 2));
}

const float & Blob::getRadius()
{
	return radius;
}

const sf::Vector2f & Blob::getPosition()
{
	return position;
}

void Blob::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(shape);
}

std::string Blob::toString()
{
	float lifeSpan;
	float growthRate;
	float moveSpeed;
	int colorRed;
	int colorGreen;
	int colorBlue;
	float radius;
	float x;
	float y;

	lua.getGlobal("this");
		lua.getField("lifeSpan").pop(lifeSpan);
		lua.getField("growthRate").pop(growthRate);
		lua.getField("moveSpeed").pop(moveSpeed);
		lua.getField("radius").pop(radius);
		lua.getField("position");
			lua.getField("x").pop(x);
			lua.getField("y").pop(y);
		lua.pop();
		lua.getField("color");
			lua.getField("r").pop(colorRed);
			lua.getField("g").pop(colorGreen);
			lua.getField("b").pop(colorBlue);
		lua.pop();
	lua.pop();

	std::stringstream string;

	string << lifeSpan << " "
		<< growthRate << " "
		<< moveSpeed << " "
		<< colorRed << " "
		<< colorGreen << " "
		<< colorBlue << " "
		<< radius << " "
		<< x << " "
		<< y << " "
		<< script;

	return string.str();
}
