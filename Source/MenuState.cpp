#include "MenuState.h"
#include <SFML\Graphics\RenderTarget.hpp>
#include <SFML\Window\Mouse.hpp>

MenuState::MenuState(sf::RenderWindow & window)
	: window(window)
	, playButton(buttonFont)
	, editButton(buttonFont)
	, quitButton(buttonFont)
{
	if (!buttonFont.loadFromFile("Assets/segoeui.ttf"))
		throw;

	playButton.setText("Play!");
	playButton.setBoxSize({ 150, 50 });
	playButton.setBoxPosition({ 0, -60 });
	playButton.setBoxActiveColor(sf::Color(0, 126, 234));
	playButton.setBoxInactiveColor(sf::Color(0, 126, 184));
	playButton.setCallback([&] {
		pushEvent({GameState::Event::PLAY});
	});

	editButton.setText("Edit");
	editButton.setBoxSize({ 150, 50 });
	editButton.setBoxPosition({ 0, 0 });
	editButton.setBoxActiveColor(sf::Color(0, 234, 126));
	editButton.setBoxInactiveColor(sf::Color(0, 204, 126));
	editButton.setCallback([&] {
		pushEvent({ GameState::Event::EDITOR });
	});

	quitButton.setText("Quit");
	quitButton.setBoxSize({ 150, 50 });
	quitButton.setBoxPosition({ 0, 60 });
	quitButton.setBoxActiveColor(sf::Color(234, 126, 0));
	quitButton.setBoxInactiveColor(sf::Color(204, 126, 0));
	quitButton.setCallback([&] {
		pushEvent({ GameState::Event::QUIT });
	});
}

MenuState::~MenuState()
{
}

void MenuState::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(playButton, states);
	target.draw(editButton, states);
	target.draw(quitButton, states);
}

void MenuState::update(float delta)
{
	sf::Vector2f pos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
	bool click = sf::Mouse::isButtonPressed(sf::Mouse::Left);
	playButton.update(pos, click);
	editButton.update(pos, click);
	quitButton.update(pos, click);
}

void MenuState::onEnter()
{
}

void MenuState::onLeave()
{
}

