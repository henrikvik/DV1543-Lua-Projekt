#include "BlobEdit.h"
#include <SFML\Graphics\RenderTarget.hpp>
#include "Resources.h"

BlobEdit::BlobEdit(Blob * blob)
{
	box.setSize({ 350, 100 });
	box.setOrigin(box.getSize() * 0.5f);
	box.setFillColor({ 100, 100, 100 });

	closeButton.setText("X");
	closeButton.setBoxSize({ 50, 50 });
	closeButton.setBoxActiveColor({ 90, 90, 90 });
	closeButton.setBoxInactiveColor({ 70, 70, 70 });

	info.setFont(Resources.Fonts.SegoeUI);
	
}

BlobEdit::~BlobEdit()
{
}

void BlobEdit::setPosition(sf::Vector2f position)
{
	box.setPosition(position);
	info.setPosition(position + sf::Vector2f(-150.f, -25.f));
	closeButton.setBoxPosition(position + sf::Vector2f(150.f, -25.f));
}

void BlobEdit::setCloseButtonCallback(std::function<void(void)> callback)
{
	closeButton.setCallback(callback);
}

void BlobEdit::update(sf::Vector2f pos, bool click)
{
	closeButton.update(pos, click);
}

void BlobEdit::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(box, states);
	target.draw(closeButton, states);
	target.draw(info, states);
}
