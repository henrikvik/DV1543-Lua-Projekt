#pragma once
#include <SFML\Graphics\RenderWindow.hpp>
#include "GameState.h"
#include "Button.h"

class MenuState : public GameState
{
public:
	MenuState(sf::RenderWindow & window);
	virtual ~MenuState();

	// Inherited via GameState
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override;
	virtual void update(float delta) override;
	virtual void onEnter() override;
	virtual void onLeave() override;
private:
	sf::RenderWindow & window;
	sf::Font buttonFont;
	Button playButton;
	Button editButton;
	Button quitButton;

	void play();
};