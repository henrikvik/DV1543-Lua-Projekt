#pragma once
#include <vector>
#include <SFML\Graphics\RenderWindow.hpp>
#include "GameState.h"
#include "Button.h"
#include "Blob.h"
#include "Increment.h"

class EditorState : public GameState
{
public:
	EditorState(sf::RenderWindow & window);
	virtual ~EditorState();

	// Inherited via GameState
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override;
	virtual void update(float delta) override;
	virtual void onEnter() override;
	virtual void onLeave() override;

private:
	sf::RenderWindow & window;
	sf::Font font;
	std::vector<Button*> buttons;
	std::vector<Blob*> blobs;
	Increment pager;
};