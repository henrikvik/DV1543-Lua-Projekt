#pragma once
#include "Blob.h"
#include "Button.h"
#include "Increment.h"
#include <SFML\Graphics\RectangleShape.hpp>

class BlobEdit : public sf::Drawable
{
public:
	BlobEdit(Blob * blob);
	virtual ~BlobEdit();

	// Inherited via Drawable
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override;
private:
	sf::RectangleShape box;
};