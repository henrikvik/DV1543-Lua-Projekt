#pragma once
#include <SFML\Graphics\Drawable.hpp>
#include <SFML\Graphics\CircleShape.hpp>
#include <SFML\System\Time.hpp>

class Blob : public sf::Drawable
{
public:
	Blob(sf::Color color, float radius);
	~Blob();

	void update(sf::Time & delta);

	void setRadius(float radius);
	void setPosition(sf::Vector2f & position);

	float getRadius();
	sf::Vector2f getPosition();

	bool checkCollision(Blob & other);
	void onCollision(Blob & other);

	// Inherited via Drawable
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override;
private:
	sf::CircleShape shape;

	sf::Vector2f position;
	float radius;

};

