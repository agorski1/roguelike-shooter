#include "Player.h"
#include "CommandQueue.h"
#include <iostream>
#include "PlayerCharacter.h"


struct PlayerMover
{
	PlayerMover(float vx, float vy)
		: velocity(vx, vy)
	{
	}

	void operator() (PlayerCharacter& player, sf::Time dt) const
	{
		player.accelerate(velocity * player.getSpeed());
	}

	sf::Vector2f velocity;
};

Player::Player()
{
	mKeyBinding[sf::Keyboard::Key::W] = Action::MoveUp;
	mKeyBinding[sf::Keyboard::Key::S] = Action::MoveDown;
	mKeyBinding[sf::Keyboard::Key::A] = Action::MoveLeft;
	mKeyBinding[sf::Keyboard::Key::D] = Action::MoveRight;
	mKeyBinding[sf::Keyboard::Key::Space] = Action::Fire;

	initializeActions();

	for (auto& pair : mActionBinding)
	{
		pair.second.category = Category::PlayerCharacter;
	}
}

void Player::assignKey(Action action, sf::Keyboard::Key key)
{
	for (auto itr = mKeyBinding.begin(); itr != mKeyBinding.end(); )
	{
		if (itr->second == action)
			mKeyBinding.erase(itr++);
		else
			++itr;
	}
	mKeyBinding[key] = action;
}

sf::Keyboard::Key Player::getAssignedKey(Action action) const
{
	for (auto pair : mKeyBinding)
	{
		if (pair.second == action)
			return pair.first;
	}

	return sf::Keyboard::Unknown;
}

void Player::handleEvent(const sf::Event event, CommandQueue& commands)
{
	
	if (event.type == sf::Event::MouseMoved)
	{
		mMousePosition = sf::Vector2f(event.mouseMove.x, event.mouseMove.y);
	}
	else if (event.type == sf::Event::KeyPressed)
	{
		// Check if pressed key appears in key binding, trigger command if so
		auto found = mKeyBinding.find(event.key.code);
		if (found != mKeyBinding.end() && !isRealtimeAction(found->second))
			commands.push(mActionBinding[found->second]);
	}

}

void Player::handleRealtimeInput(CommandQueue& commands)
{
	for (auto pair : mKeyBinding)
	{
		if (sf::Keyboard::isKeyPressed(pair.first) && isRealtimeAction(pair.second))
			commands.push(mActionBinding[pair.second]);
	}
}

const sf::Vector2f& Player::getMousePosition() const
{
	return mMousePosition;
}

void Player::initializeActions()
{
	mActionBinding[MoveLeft].action = derivedAction<PlayerCharacter>(PlayerMover(-1, 0));
	mActionBinding[MoveRight].action = derivedAction<PlayerCharacter>(PlayerMover(+1, 0));
	mActionBinding[MoveUp].action = derivedAction<PlayerCharacter>(PlayerMover(0, -1));
	mActionBinding[MoveDown].action = derivedAction<PlayerCharacter>(PlayerMover(0, +1));
	/*mActionBinding[Action::Fire].action = derivedAction<Aircraft>(std::bind(&Aircraft::fire, std::placeholders::_1));
	mActionBinding[Action::LaunchMissile].action = derivedAction<Aircraft>(std::bind(&Aircraft::launchMissile, std::placeholders::_1));*/
}

bool Player::isRealtimeAction(Action action)
{
	switch (action)
	{
	case Player::MoveLeft:
	case Player::MoveRight:
	case Player::MoveUp:
	case Player::MoveDown:
	case Player::Fire:
		return true;

	default:
		return false;
	}
}
