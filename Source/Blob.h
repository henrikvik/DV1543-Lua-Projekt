#pragma once
#include <SFML\Graphics\Drawable.hpp>
#include <SFML\Graphics\CircleShape.hpp>
#include <SFML\System\Time.hpp>
#include "LuaState.h"

class Blob : public sf::Drawable
{
public:
	Blob(float lifeSpan, float growthRate, float moveSpeed, int colorRed, int colorGreen, int colorBlue, float radius, float x, float y, const std::string & script);
	virtual ~Blob();

	virtual void update(float delta);
	void checkCollision(Blob & other);


	LuaState * getLuaState();
	const float & getRadius();
	const sf::Vector2f & getPosition();

	float getDistance(const sf::Vector2f & point);

	// Inherited via Drawable
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override;

	std::string toString();

	bool operator=(const Blob & blob)
	{
		return blob.uid == uid;
	}
private:
	static size_t UID_BASE;
	const size_t uid;
	LuaState lua;


	sf::CircleShape shape;
	sf::Vector2f position;
	std::string script;
	float radius;
};

