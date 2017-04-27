#pragma once
#include "Blob.h"
#include "LuaState.h"

class PlayerBlob : public Blob
{
public:
	PlayerBlob(sf::Color color, float radius, const char * luaPath);
	using Blob::Blob;

	// Inherited via Blob
	virtual void update(sf::Time & delta) override;
	virtual void onCollision(Blob & other) override;
private:
	LuaState lua;

	sf::Vector2f getInputDirection();
};

