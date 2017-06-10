#pragma once
#include "Blob.h"
#include "Button.h"
#include "Increment.h"

class BlobEdit : public sf::Drawable
{
public:
	BlobEdit(Blob * blob);
	virtual ~BlobEdit();

	// Inherited via Drawable
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override;
private:
	
};