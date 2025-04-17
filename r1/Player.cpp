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

Player::Player(sf::RenderTarget& target)
	: mTarget(target)
{
	mKeyBinding[sf::Keyboard::Key::W] = Action::MoveUp;
	mKeyBinding[sf::Keyboard::Key::S] = Action::MoveDown;
	mKeyBinding[sf::Keyboard::Key::A] = Action::MoveLeft;
	mKeyBinding[sf::Keyboard::Key::D] = Action::MoveRight;
	mKeyBinding[sf::Keyboard::Key::R] = Action::Reload;
	
	mMouseBinding[sf::Mouse::Button::Left] = Action::Fire;

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

void Player::handleEvent(const sf::Event event, CommandQueue& commands, const sf::View& worldView)
{

	if (event.type == sf::Event::KeyPressed)
	{
		// Check if pressed key appears in key binding, trigger command if so
		auto found = mKeyBinding.find(event.key.code);
		if (found != mKeyBinding.end() && !isRealtimeAction(found->second))
			commands.push(mActionBinding[found->second]);
	}

}

void Player::handleRealtimeInput(CommandQueue& commands, const sf::View& worldView)
{
	for (auto pair : mKeyBinding)
	{
		if (sf::Keyboard::isKeyPressed(pair.first) && isRealtimeAction(pair.second))
			commands.push(mActionBinding[pair.second]);
	}

	for (auto pair : mMouseBinding)
	{
		if (sf::Mouse::isButtonPressed(pair.first) && isRealtimeAction(pair.second))
			if (pair.second == Action::Fire)
			{
				Command fireCommand;
				fireCommand.category = Category::PlayerCharacter;
				fireCommand.action = derivedAction<PlayerCharacter>([&](PlayerCharacter& player, sf::Time)
					{
						player.fire(commands);
					});
				commands.push(fireCommand);
			}
			else
				commands.push(mActionBinding[pair.second]);
	}


	sf::Vector2i mousePixelPos = sf::Mouse::getPosition(); // Pozycja myszy w pikselach
	sf::Vector2f mouseWorldPos = mTarget.mapPixelToCoords(mousePixelPos, worldView); // Pozycja w świecie
	mMousePositionLocal = mousePixelPos;
	mMousePositionWorld = mouseWorldPos; // Aktualizacja pozycji myszy

	Command aimCommand;
	aimCommand.category = Category::PlayerCharacter;
	aimCommand.action = [mouseWorldPos](SceneNode& node, sf::Time)
		{
			PlayerCharacter& character = static_cast<PlayerCharacter&>(node);
			character.aimAt(mouseWorldPos);
		};
	commands.push(aimCommand);

}

const sf::Vector2f& Player::getMousePositionWorld() const
{
	return mMousePositionWorld;
}


const sf::Vector2i& Player::getMousePositionLocal() const
{
	return mMousePositionLocal;
}


void Player::initializeActions()
{
	mActionBinding[MoveLeft].action = derivedAction<PlayerCharacter>(PlayerMover(-1, 0));
	mActionBinding[MoveRight].action = derivedAction<PlayerCharacter>(PlayerMover(+1, 0));
	mActionBinding[MoveUp].action = derivedAction<PlayerCharacter>(PlayerMover(0, -1));
	mActionBinding[MoveDown].action = derivedAction<PlayerCharacter>(PlayerMover(0, +1));
	mActionBinding[Reload].action = derivedAction<PlayerCharacter>([](PlayerCharacter& player, sf::Time)
		{
			player.reloadWeapon();
		});
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
