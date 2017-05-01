#pragma once
#include <SFML\Graphics\Drawable.hpp>
#include <SFML\Graphics\CircleShape.hpp>
#include <SFML\System\Time.hpp>
#include "LuaState.h"

class Blob : public sf::Drawable
{
public:
	Blob(LuaState & lua, sf::Color color, float radius, const char * luaScript);
	virtual ~Blob();

	virtual void update(sf::Time & delta);
	virtual void onCollision(Blob & other);

	inline const float & getRadius();
	inline const sf::Vector2f & getPosition();

	bool checkCollision(Blob & other);

	// Inherited via Drawable
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override;
private:
	static size_t UID_BASE;
	const size_t uid;
	LuaState & lua;


	sf::CircleShape shape;
	sf::Vector2f position;
	float radius;
};

