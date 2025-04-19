#include "HUD.h"
#include "SFML/Graphics/Texture.hpp"
#include "Utility.h"

HUD::HUD(sf::RenderTarget& outputTarget)
	: mTarget(outputTarget)
	, mTextures()
	, mFonts()
	, mCrosshair()
{
	loadTextures();
	loadFonts();

	mCrosshair.setTexture(mTextures.get(Textures::Crosshair));
	centerOrigin(mCrosshair);

    // Inicjalizuj pasek zdrowia - tło
    mHealthBarBackground.setSize(sf::Vector2f(200.f, 20.f)); 
    mHealthBarBackground.setFillColor(sf::Color(50, 50, 50)); 
    mHealthBarBackground.setPosition(10.f, 10.f); 
    mHealthBarBackground.setOutlineColor(sf::Color::Black);
    mHealthBarBackground.setOutlineThickness(2.f);

    // Inicjalizuj pasek zdrowia - wypełnienie
    mHealthBarFill.setSize(sf::Vector2f(200.f, 20.f));
    mHealthBarFill.setFillColor(sf::Color::Red);
    mHealthBarFill.setPosition(10.f, 10.f);

    // Inicjalizuj tekst HP
    mHealthText.setFont(mFonts.get(Fonts::Stats));
    mHealthText.setCharacterSize(16);
    mHealthText.setFillColor(sf::Color::White);
    mHealthText.setOutlineColor(sf::Color::Black); 
    mHealthText.setOutlineThickness(1.f);
    mHealthText.setString("0/0");
    centerOrigin(mHealthText); 
    mHealthText.setPosition(10.f + 100.f, 10.f + 10.f); 

    mAmmoText.setFont(mFonts.get(Fonts::Stats));
    mAmmoText.setCharacterSize(16);
    mAmmoText.setFillColor(sf::Color::White);
    mAmmoText.setOutlineColor(sf::Color::Black);
    mAmmoText.setOutlineThickness(1.f);
    mAmmoText.setString("0/0");
    mAmmoText.setPosition(10.f, 40.f);

}

void HUD::update(sf::Time dt, const sf::Vector2i& mousePos)
{
    mCrosshair.setPosition(sf::Vector2f(mousePos));
	updateHealthDisplay();
    updateAmmoDisplay();
}

void HUD::draw()
{
    mTarget.setView(mTarget.getDefaultView());

    mTarget.draw(mCrosshair);
    drawHealthDisplay();
    drawAmmoDisplay();
}

void HUD::onStatsUpdated(const PlayerStats& stats)
{
	mStats = stats;
}

void HUD::loadTextures()
{
	mTextures.load(Textures::Crosshair, "assets/textures/crosshair.png");
}

void HUD::loadFonts()
{
	mFonts.load(Fonts::Stats, "assets/fonts/littlehitbox.ttf");
}

void HUD::updateHealthDisplay()
{
    if (mStats.maxHp > 0) // Unikamy dzielenia przez zero
    {
        float healthRatio = static_cast<float>(mStats.hp) / mStats.maxHp;
        float fillWidth = 200.f * healthRatio; // 200 to szerokość tła
        mHealthBarFill.setSize(sf::Vector2f(fillWidth, 20.f));

        if (healthRatio > 0.5f)
            mHealthBarFill.setFillColor(sf::Color::Green);
        else if (healthRatio > 0.25f)
            mHealthBarFill.setFillColor(sf::Color::Yellow);
        else
            mHealthBarFill.setFillColor(sf::Color::Red);
    }
    else
    {
        mHealthBarFill.setSize(sf::Vector2f(0.f, 20.f));
    }

    mHealthText.setString(std::to_string(mStats.hp) + "/" + std::to_string(mStats.maxHp));
    centerOrigin(mHealthText); // Ponownie wyśrodkuj, bo tekst się zmienił
    mHealthText.setPosition(10.f + 100.f, 10.f + 10.f); // Środek paska zdrowia
}

void HUD::updateAmmoDisplay()
{
    mAmmoText.setString(std::to_string(mStats.currentAmmo) + "/" + std::to_string(mStats.totalAmmo));
    mAmmoText.setPosition(10.f, 40.f); // Upewnij się, że pozycja jest poprawna
}

void HUD::drawHealthDisplay()
{
    mTarget.draw(mHealthBarBackground);
    mTarget.draw(mHealthBarFill);
    mTarget.draw(mHealthText); 
}

void HUD::drawAmmoDisplay()
{
    mTarget.draw(mAmmoText);
}


