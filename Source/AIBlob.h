#pragma once
#include "Blob.h"
#include "LuaState.h"

class AIBlob : public Blob
{
public:
	AIBlob(sf::Color color, float radius, const char * aiPath);
	virtual ~AIBlob();

	// Inherited via Blob
	virtual void update(sf::Time & delta) override;
	virtual void onCollision(Blob & other) override;
private:
	LuaState lua;


};

