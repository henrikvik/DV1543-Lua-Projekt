#pragma once
#include "Button.h"

class Increment : public sf::Drawable, public sf::Transformable
{
public:
	Increment(sf::Font & font);
	virtual ~Increment();

	void setValue(float value);
	void setIncrement(float increment);
	void setMinValue(float minValue);
	void setMaxValue(float maxValue);
	void setName(const sf::String & name);

	void setPosition(sf::Vector2f position);

	float getValue();

	// Inherited via Drawable
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override;
	void update(sf::Vector2f position, bool click);
private:
	sf::Text text;
	std::string name;

	float value;
	float increment;
	float minValue;
	float maxValue;

	Button incButton;
	Button decButton;
};