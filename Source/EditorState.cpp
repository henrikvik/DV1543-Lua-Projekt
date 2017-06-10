#include "EditorState.h"
#include <SFML\Graphics\Font.hpp>
#include <SFML\Window\Mouse.hpp>
#include "FileHandler.h"

EditorState::EditorState(sf::RenderWindow & window)
	: window(window)
	, pager(font)
{
	font.loadFromFile("Assets/segoeui.ttf");

	{
		Button * button = new Button(font);
		button->setText("Back");
		button->setBoxSize({ 100, 50 });
		button->setBoxPosition({-325, 250});
		button->setBoxActiveColor({ 220, 70, 50 });
		button->setBoxInactiveColor({ 200, 50, 50 });
		button->setCallback([&] {
			pushEvent({ GameState::Event::MENU });
		});
		buttons.push_back(button);
	}

	{
		Button * button = new Button(font);
		button->setText("Save");
		button->setBoxSize({ 100, 50 });
		button->setBoxPosition({ 325, 250 });
		button->setBoxActiveColor({ 70, 220, 50 });
		button->setBoxInactiveColor({ 50, 200, 50 });
		button->setCallback([&] {
			FileHandler::writeToFile("Assets/Blobs.txt", blobs);
		});
		buttons.push_back(button);
	}

	{
		Button * button = new Button(font);
		button->setText("Add");
		button->setBoxSize({ 100, 50 });
		button->setBoxPosition({ 0, 250 });
		button->setBoxActiveColor({ 70, 50, 220 });
		button->setBoxInactiveColor({ 50, 50, 200 });
		button->setCallback([&] {
		});
		buttons.push_back(button);
	}

	pager.setIncrement(1);
	pager.setMaxValue(10);
	pager.setMinValue(1);
	pager.setName("Page");
	pager.setValue(1);
	pager.setPosition({ 0, 190 });
}

EditorState::~EditorState()
{
	for (Button * button : buttons)
	{
		delete button;
	}

	onLeave();
}

void EditorState::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	for (Button * button : buttons)
	{
		target.draw(*button);
	}

	target.draw(pager, states);
}

void EditorState::update(float delta)
{
	sf::Vector2f pos = window.mapPixelToCoords(sf::Mouse::getPosition(window));


	static bool lastFrame = false;
	static sf::Time timer;
	
	bool thisFrame = sf::Mouse::isButtonPressed(sf::Mouse::Left);
	bool click = thisFrame && !lastFrame;
	lastFrame = thisFrame;


	for (Button * button : buttons)
	{
		button->update(pos, click);
	}
	pager.update(pos, click);
}

void EditorState::onEnter()
{
	blobs = FileHandler::readFromFile("Assets/Blobs.txt");
}

void EditorState::onLeave()
{
	for (Blob * blob : blobs)
	{
		delete blob;
	}
	blobs.clear();
}
