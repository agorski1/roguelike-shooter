#include "GameState.h"
#include "MusicPlayer.h"
#include "StateStack.h"
#include "PlayerCharacter.h"

GameState::GameState(StateStack& stack, Context context)
	: State(stack, context)
	, mWorld(*context.window, *context.fonts, *context.sounds)
	, mPlayer(*context.player)
	, mHUD(*context.window)
{
	context.music->setVolume(10);
	context.music->play(Music::MissionTheme);
	
	PlayerCharacter* player = mWorld.getPlayerCharacter();
	if (player)
	{
		player->addStatsObserver(&mHUD);
	}

}

void GameState::draw()
{
	mWorld.draw();
	mHUD.draw();
}

bool GameState::update(sf::Time dt)
{
	mWorld.update(dt, mPlayer.getMousePositionWorld());
	mHUD.update(dt, mPlayer.getMousePositionLocal());
	CommandQueue& commands = mWorld.getCommandQueue();
	mPlayer.handleRealtimeInput(commands, mWorld.getWorldView());

	return true;
}

bool GameState::handleEvent(const sf::Event& event)
{
	CommandQueue& commands = mWorld.getCommandQueue();
	mPlayer.handleEvent(event, commands, mWorld.getWorldView());

	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
		requestStackPush(States::Pause);

	return true;
}
