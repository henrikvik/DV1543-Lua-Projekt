#include "Button.h"
#include <SFML\Graphics\Font.hpp>
#include <SFML\Graphics\RenderTarget.hpp>
#include <SFML\Graphics\RenderStates.hpp>
#include <SFML\Window\Mouse.hpp>

Button::Button(sf::Font & font)
{
	this->text.setFont(font);
	callback = nullptr;
}

Button::~Button()
{
}

void Button::setText(sf::String text)
{
	this->text.setString(text);
	sf::FloatRect textRect = this->text.getLocalBounds();
	this->text.setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);
}

void Button::setTextColor(sf::Color color)
{
	text.setFillColor(color);
}

void Button::setTextSize(unsigned int size)
{
	text.setCharacterSize(size);
	sf::FloatRect textRect = text.getLocalBounds();
	text.setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);
}

void Button::setBoxActiveColor(sf::Color color)
{
	activeColor = color;
}

void Button::setBoxInactiveColor(sf::Color color)
{
	box.setFillColor(color);
	inactiveColor = color;
}


void Button::setBoxSize(sf::Vector2f size)
{
	box.setSize(size);
	box.setOrigin(size * 0.5f);
	text.setPosition(size * 0.5f);

}

void Button::setBoxPosition(sf::Vector2f position)
{
	box.setPosition(position);
}

void Button::setCallback(std::function<void(void)> callback)
{
	this->callback = callback;
}

void Button::update(sf::Vector2f position, bool click)
{
	sf::FloatRect bounds = box.getGlobalBounds();
	sf::Vector2f mPos((float)position.x, (float)position.y);
	if (bounds.contains(mPos))
	{
		box.setFillColor(activeColor);
		if (click && callback != nullptr)
			callback();
	}
	else
	{
		box.setFillColor(inactiveColor);
	}
}

void Button::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(box, states);
	target.draw(text, sf::RenderStates(box.getTransform()));
}
