#pragma once
#include <SFML\Graphics\Drawable.hpp>
#include <SFML\Graphics\RectangleShape.hpp>
#include <SFML\Graphics\Text.hpp>
#include <SFML\Graphics\Rect.hpp>
#include <functional>

class Button : public sf::Drawable
{
public:
	Button(sf::Font & font);
	virtual ~Button();

	void setText(sf::String text);
	void setTextColor(sf::Color color);
	void setTextSize(unsigned int size);
	void setBoxActiveColor(sf::Color color);
	void setBoxInactiveColor(sf::Color color);
	void setBoxSize(sf::Vector2f size);
	void setBoxPosition(sf::Vector2f position);
	void setCallback(std::function<void(void)> callback);

	void update(sf::Vector2f position, bool click = false);

	// Inherited via Drawable
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override;
private:
	sf::RectangleShape box;
	sf::Text text;
	sf::Color activeColor;
	sf::Color inactiveColor;
	std::function<void(void)> callback;
};