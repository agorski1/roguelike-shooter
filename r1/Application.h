#pragma once
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/System/Time.hpp"
#include "ResourceHolder.h"
#include "ResourceIdentifiers.h"
#include "SFML/System/Time.hpp"
#include "SFML/Graphics/Text.hpp"
#include "StateStack.h"

#include"MusicPlayer.h"
#include "SoundPlayer.h"
#include "Player.h"

class Application
{
public:
	Application();
	void run();

private:
	void processInput();
	void update(sf::Time deltaTime);
	void render();

	void updateStatistics(sf::Time dt);
	void registerStates();


private:
	static const sf::Time TimePerFrame;

	sf::RenderWindow mWindow;
	TextureHolder  mTexture;
	FontHolder mFonts;
	Player mPlayer;

	MusicPlayer mMusic;
	SoundPlayer mSounds;
	StateStack mStateStack;

	sf::Text mStatisticsText;
	sf::Time mStatisticsUpdateTime;
	std::size_t mStatisticsNumFrames;

};

