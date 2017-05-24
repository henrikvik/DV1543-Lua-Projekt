#pragma once
#include <vector>
#include <map>
#include <SFML\Graphics\RenderWindow.hpp>
#include <SFML\System\Clock.hpp>
#include "Blob.h"
#include "GameState.h"

class Engine : public sf::Drawable
{
public:
	Engine();
	~Engine();

	void start();

	void addBlob(sf::Color color, const sf::Vector2f & position, float radius, const char * luaScript);

	void quitGame();

private:
	enum State {MENU, PLAY, EDITOR};
	std::map<State, GameState*> states;
	GameState * currentState;

	sf::RenderWindow window;
	sf::View camera;

	bool isRunning;

	typedef std::vector<Blob*> BlobList;
	BlobList blobs;

	void pollEvents();
	void update(sf::Time & delta);
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override;

	static int lua_quitGame(Engine * engine);
	static int lua_getClosestBlob(LuaState * lua, Blob * blob, BlobList* blobs);
	static int lua_addBlob(LuaState * lua, Engine * engine);
	static int lua_getInputDirection(LuaState * lua);
};

