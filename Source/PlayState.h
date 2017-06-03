#pragma once
#include <vector>
#include "GameState.h"
#include "Blob.h"

class PlayState : public GameState
{
public:
	PlayState();
	virtual ~PlayState();

	// Inherited via GameState
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override;
	virtual void update(float delta) override;
	virtual void onEnter() override;
	virtual void onLeave() override;

private:
	typedef std::vector<Blob*> BlobList;
	BlobList blobs;

	void addBlob(sf::Color color, const sf::Vector2f & position, float radius, const char * luaScript);

	static int lua_quitGame(PlayState * state);
	static int lua_getClosestBlob(LuaState * lua, Blob * blob, BlobList* blobs);
	static int lua_addBlob(LuaState * lua, PlayState *  state);
	static int lua_getInputDirection(LuaState * lua);
};