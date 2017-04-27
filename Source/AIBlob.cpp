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
	sf::Vector2f position;

	lua.getGlobal("this")
		.push(getRadius()).setField("radius")
	.pop();

	lua.getGlobal("update")
		.push(delta.asSeconds())
		.call(1, 0);

	lua.getGlobal("this")
		.getField("position")
			.getField("x").pop(position.x)
			.getField("y").pop(position.y)
		.pop()
	.pop();

	setPosition(position);
}

void AIBlob::onCollision(Blob & other)
{
}
