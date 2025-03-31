#include "Weapon.h"
#include "DataTables.h"
#include "Utility.h"
#include "CommandQueue.h"


namespace
{
	const std::vector<WeaponData> Table = initializeWeaponData();
}

Weapon::Weapon(WeaponType weaponType, const TextureHolder& textures)
	: mWeaponType(weaponType)
	, mSprite()
	, mMagazineSize(Table[mWeaponType].magazineSize)
	, mCurrentAmmo(Table[mWeaponType].magazineSize)
	, mTotalAmmo(Table[mWeaponType].totalAmmo)
	, mReloadTime(Table[mWeaponType].reloadTime)
	, mFireRate(Table[mWeaponType].fireRate)
	, mTimeSinceLastShot(sf::Time::Zero) 
	, mIsFlipped(false)
{
	mSprite.setTexture(textures.get(Table[mWeaponType].texture));
	mSprite.setOrigin(0.f, mSprite.getLocalBounds().height / 2.f);
	mSprite.setPosition(-20.f, 15.f);
	// Przykładowy offset - dostosuj do swojego sprite'a
	//mHandOffset = sf::Vector2f(25.f, 0.f); // 25 pikseli na prawo od środka
}

void Weapon::fire(CommandQueue& commands)
{
    std::cout << "Current ammo" << mCurrentAmmo << std::endl;
	std::cout << "Czas od ostatniego strzału: " << mTimeSinceLastShot.asSeconds() << std::endl;
	if ((mCurrentAmmo > 0) && (mTimeSinceLastShot >= sf::seconds(1.f / mFireRate)))
	{
		mCurrentAmmo--;
		mTimeSinceLastShot = sf::Time::Zero;

        std::cout << "Strzał!" << std::endl;
	}
}


void Weapon::update(sf::Time dt, CommandQueue& commands)
{
	mTimeSinceLastShot += dt;

	if (mAimDirection.x == 0.f && mAimDirection.y == 0.f)
		return;

	float angle = std::atan2(mAimDirection.y, mAimDirection.x) * 180.f / 3.14159265f;

	bool shouldFlip = (angle > 90.f || angle < -90.f);

	if (shouldFlip != mIsFlipped)
	{
		mIsFlipped = shouldFlip;
		mSprite.setScale(1.f, shouldFlip ? -1.f : 1.f);  
	}

	// Aktualizacja rotacji sprite’a broni
	mSprite.setRotation(angle);
}

void Weapon::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(mSprite, states);
}

void Weapon::setAimDirection(sf::Vector2f direction)
{
	if (direction != sf::Vector2f(0.f, 0.f))
		mAimDirection = unitVector(direction);
}