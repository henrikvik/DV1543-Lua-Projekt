#include "BlobEdit.h"
#include <SFML\Graphics\RenderTarget.hpp>

BlobEdit::BlobEdit(Blob * blob)
{
	box.setSize({ 200, 100 });
	box.setFillColor({ 100, 100, 100 });
}

BlobEdit::~BlobEdit()
{
}

void BlobEdit::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(box, states);
}
