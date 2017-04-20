#pragma once
#include "Blob.h"

class PlayerBlob : public Blob
{
public:
	using Blob::Blob;

	// Inherited via Blob
	virtual void update(sf::Time & delta) override;
	virtual void onCollision(Blob & other) override;
private:
};

