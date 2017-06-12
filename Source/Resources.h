#pragma once
#include <SFML\Graphics\Font.hpp>

static class Resource
{
public:
	Resource()
	{
		if (!Fonts.SegoeUI.loadFromFile("Assets/segoeui.ttf"))
			throw printf("Could not load font");
	}

	struct Fonts
	{
		sf::Font SegoeUI;
	} Fonts;

} Resources;