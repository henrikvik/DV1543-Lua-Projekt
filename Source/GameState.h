#pragma once
#include <SFML\Graphics\Drawable.hpp>
#include <queue>



class GameState :
	public sf::Drawable
{
public:
	virtual void update(float delta) = 0;
	virtual void onEnter() = 0;
	virtual void onLeave() = 0;

	struct Event
	{
		enum Type { QUIT, MENU, PLAY, EDITOR };
		Type type;
	};

	void pushEvent(const Event & event)
	{
		eventQeueu.push(event);
	}

	bool pollEvent(Event & event)
	{
		bool foundEvent = false;
		if (eventQeueu.size() > 0)
		{
			foundEvent = true;
			event = eventQeueu.front();
			eventQeueu.pop();
		}
		return foundEvent;
	}
private:
	std::queue<Event> eventQeueu;
};

