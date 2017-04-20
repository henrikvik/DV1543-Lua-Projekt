#pragma once
#include <SFML\Graphics\RenderWindow.hpp>
#include <SFML\System\Clock.hpp>
#include "Blob.h"
#include "vector"
#include <memory>

class Engine : public sf::Drawable
{
public:
	Engine();
	~Engine();

	void run();

private:
	sf::RenderWindow window;
	sf::View camera;

	bool isRunning;

	std::vector<std::unique_ptr<Blob>> blobs;

	void pollEvents();
	void update(sf::Time & delta);
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override;
};

