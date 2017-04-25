#include "AIBlob.h"

AIBlob::AIBlob(sf::Color color, float radius, const char * aiPath)
	: Blob(color, radius)
{
	lua.loadOpenLibs().dofile(aiPath);
}

AIBlob::~AIBlob()
{
}

void AIBlob::update(sf::Time & delta)
{
	lua.push(getRadius()).set("radius");

	lua.get("update").push(delta.asSeconds()).call(1, 0);

	//sf::Vector2f position;
	//lua.get("me.x").pop(position.x);
	//lua.get("me.y").pop(position.y);
	//setPosition(position);
}

void AIBlob::onCollision(Blob & other)
{
}
