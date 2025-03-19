#pragma once
#include <vector>
#include "Button.h"
#include "Container.h"
#include "State.h"

class StateStack;

class MenuState : public State
{
public:
	MenuState(StateStack& stack, Context context);

	virtual void draw();
	virtual bool update(sf::Time dt);
	virtual bool handleEvent(const sf::Event& event);


private:
	sf::Sprite mBackgroundSprite;
	GUI::Container mGUIContainer;
};

