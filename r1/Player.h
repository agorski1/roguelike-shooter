#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include "Command.h"

class CommandQueue;

class Player
{
public:
	Player();
	enum Action
	{
		MoveLeft,
		MoveRight,
		MoveUp,
		MoveDown,
		Fire,
		MoveMouse,
		ActionCount,
	};

	void assignKey(Action action, sf::Keyboard::Key key);
	sf::Keyboard::Key getAssignedKey(Action action) const;

	void handleEvent(const sf::Event event, CommandQueue& commands);
	void handleRealtimeInput(CommandQueue& commands);

	const sf::Vector2f& getMousePosition() const;

private:
	void initializeActions();

private:
	static bool isRealtimeAction(Action action);

private:
	std::map<sf::Keyboard::Key, Action> mKeyBinding;
	std::map<Action, Command> mActionBinding;

	sf::Vector2f mMousePosition;
};

