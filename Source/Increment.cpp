#include "Increment.h"
#include <SFML\Graphics\RenderTarget.hpp>
#include <sstream>
Increment::Increment(sf::Font & font)
{
	incButton.setText("+");
	incButton.setBoxSize({ 50, 50 });
	incButton.setBoxPosition({ 100, 0 });
	incButton.setBoxActiveColor({ 70, 170, 70 });
	incButton.setBoxInactiveColor({ 50, 150, 50 });
	incButton.setCallback([&] {
		value += increment;
		if (value > maxValue) value = maxValue;
		setValue(value);
	});

	decButton.setText("-");
	decButton.setBoxSize({ 50, 50 });
	decButton.setBoxPosition({ -100, 0 });
	decButton.setBoxActiveColor({ 170, 70, 70 });
	decButton.setBoxInactiveColor({ 150, 50, 50 });
	decButton.setCallback([&] {
		value -= increment;
		if (value < minValue) value = minValue;
		setValue(value);
	});

	text.setFont(font);
	text.setFillColor(sf::Color::Black);


	name = "";

	value = 0;
	increment = 0;
	minValue = 0;
	maxValue = 0;
}

Increment::~Increment()
{
}

void Increment::setValue(float value)
{
	this->value = value;
	std::stringstream stream;
	stream << name << ": " << value;
	text.setString(stream.str());
	sf::FloatRect bounds = text.getLocalBounds();
	text.setOrigin({ bounds.width * 0.5f, bounds.height * 0.5f + 5});
}

void Increment::setIncrement(float increment)
{
	this->increment = increment;
}

void Increment::setMinValue(float minValue)
{
	this->minValue = minValue;
}

void Increment::setMaxValue(float maxValue)
{
	this->maxValue = maxValue;
}

void Increment::setName(const sf::String & name)
{
	this->name = name;
	std::stringstream stream;
	stream << this->name << ": " << value;
	text.setString(stream.str());

	sf::FloatRect bounds = text.getLocalBounds();
	text.setOrigin({bounds.width * 0.5f, bounds.height * 0.5f + 5});
}

void Increment::setPosition(sf::Vector2f position)
{
	incButton.setBoxPosition(position + sf::Vector2f( 100, 0));
	decButton.setBoxPosition(position + sf::Vector2f( -100, 0 ));
	text.setPosition(position);
}

float Increment::getValue()
{
	return value;
}

void Increment::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(text, states);
	target.draw(incButton, states);
	target.draw(decButton, states);
}

void Increment::update(sf::Vector2f position, bool click)
{
	incButton.update(position, click);
	decButton.update(position, click);
}