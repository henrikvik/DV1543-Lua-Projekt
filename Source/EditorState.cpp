#include "EditorState.h"
#include <SFML\Graphics\Font.hpp>
#include <SFML\Window\Mouse.hpp>
#include "FileHandler.h"

EditorState::EditorState(sf::RenderWindow & window)
	: window(window)
{
	font.loadFromFile("Assets/segoeui.ttf");

	{
		Button * button = new Button();
		button->setText("Back");
		button->setBoxSize({ 100, 50 });
		button->setBoxPosition({ -325, 250 });
		button->setBoxActiveColor({ 220, 70, 50 });
		button->setBoxInactiveColor({ 200, 50, 50 });
		button->setCallback([&] {
			pushEvent({ GameState::Event::MENU });
		});
		buttons.push_back(button);
	}

	{
		Button * button = new Button();
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
		Button * button = new Button();
		button->setText("Add");
		button->setBoxSize({ 100, 50 });
		button->setBoxPosition({ 0, 250 });
		button->setBoxActiveColor({ 70, 50, 220 });
		button->setBoxInactiveColor({ 50, 50, 200 });
		button->setCallback([&] {
			blobs.push_back(new Blob());
			remakeList = true;
		});
		buttons.push_back(button);
	}

	remakeList = false;
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
	for (BlobEdit * blobEdit: blobEdits)
	{
		target.draw(*blobEdit);
	}
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

	for (BlobEdit * blobEdit : blobEdits)
	{
		blobEdit->update(pos, click);
	}


	if (remakeList) remakeBlobEditList();
}

void EditorState::onEnter()
{
	blobs = FileHandler::readFromFile("Assets/Blobs.txt");
	remakeBlobEditList();
}

void EditorState::remakeBlobEditList()
{
	remakeList = false;
	for (BlobEdit * blobEdit : blobEdits)
	{
		delete blobEdit;
	}
	blobEdits.clear();

	static float offsetX = -190, offsetY = -215;
	for (int i = 0, size = blobs.size(); i < size; i++)
	{
		BlobEdit * blobEdit = new BlobEdit(blobs[i]);
		blobEdit->setPosition({
			offsetX + (i % 2) * (350 + 30),
			offsetY + (i / 2) * 125.0f
		});

		blobEdit->setCloseButtonCallback([&, i] {
			blobs.erase(blobs.begin() + i);
			remakeList = true;
			
		});
		blobEdits.push_back(blobEdit);
	}
}

void EditorState::onLeave()
{
	for (Blob * blob : blobs)
	{
		delete blob;
	}
	blobs.clear();
	for (BlobEdit * blobEdit : blobEdits)
	{
		delete blobEdit;
	}
	blobEdits.clear();
}
