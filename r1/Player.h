#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include "Command.h"

class CommandQueue;

class Player
{
public:
	Player(sf::RenderTarget& target);
	enum Action
	{
		MoveLeft,
		MoveRight,
		MoveUp,
		MoveDown,
		Fire,
		MoveMouse,
		Reload,
		ActionCount,
	};

	void assignKey(Action action, sf::Keyboard::Key key);
	sf::Keyboard::Key getAssignedKey(Action action) const;

	void handleEvent(const sf::Event event, CommandQueue& commands, const sf::View& worldView);
	void handleRealtimeInput(CommandQueue& commands, const sf::View& worldView);

	const sf::Vector2f& getMousePosition() const;

private:
	void initializeActions();

private:
	static bool isRealtimeAction(Action action);

private:
	sf::RenderTarget& mTarget;
	std::map<sf::Keyboard::Key, Action> mKeyBinding;
	std::map<sf::Mouse::Button, Action> mMouseBinding;
	std::map<Action, Command> mActionBinding;
	sf::Vector2f mMousePosition;
};

