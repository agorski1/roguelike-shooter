#pragma once
#include "State.h"
#include "SFML/Graphics.hpp"
#include "World.h"
#include "Player.h"
#include "HUD.h"

class GameState : public State
{
public:
	GameState(StateStack& stack, Context context);

	virtual void draw();
	virtual bool update(sf::Time dt);
	virtual bool handleEvent(const sf::Event& event);

private:
	World mWorld;
	Player mPlayer;
	HUD mHUD;
};

