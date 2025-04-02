#pragma once
#include "SFML/Graphics/RenderTarget.hpp"
#include "SFML/System/Time.hpp"
#include "SFML/System/NonCopyable.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/System/Vector2.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/Text.hpp"
#include "ResourceIdentifiers.h"
#include "ResourceHolder.h"

#include "StatsObserver.h"

class HUD : private sf::NonCopyable, public StatsObserver

{
public:
	HUD(sf::RenderTarget& outputTarget);
	void update(sf::Time dt, const sf::Vector2i& mousePos);
	void draw();

	void onStatsUpdated(const PlayerStats& stats) override;

private:
	void loadTextures();
	void loadFonts();

	void updateHealthDisplay();
	void updateAmmoDisplay();

	void drawHealthDisplay();
	void drawAmmoDisplay();

private:
	sf::RenderTarget& mTarget;
	TextureHolder mTextures;
	FontHolder mFonts;
	sf::Sprite mCrosshair;

	PlayerStats mStats;

	sf::RectangleShape mHealthBarBackground;
	sf::RectangleShape mHealthBarFill;
	sf::Text mHealthText;
	sf::Text mAmmoText;
};

