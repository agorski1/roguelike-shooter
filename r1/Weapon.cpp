#include "Weapon.h"
#include "DataTables.h"
#include "Utility.h"
#include "CommandQueue.h"
#include "PlayerCharacter.h"

namespace
{
	const std::vector<WeaponData> Table = initializeWeaponData();
}

Weapon::Weapon(WeaponType weaponType, const TextureHolder& textures, PlayerCharacter* owner, sf::Vector2f handOffset)
	: mWeaponType(weaponType)
	, mSprite()
	, mMagazineSize(Table[mWeaponType].magazineSize)
	, mCurrentAmmo(Table[mWeaponType].magazineSize)
	, mTotalAmmo(Table[mWeaponType].totalAmmo)
	, mReloadTime(Table[mWeaponType].reloadTime)
	, mFireRate(Table[mWeaponType].fireRate)
	, mTimeSinceLastShot(sf::Time::Zero) 
	, mIsFlipped(false)
	, mIsReloading(false)
	, mOwner(owner)
{
	mSprite.setTexture(textures.get(Table[mWeaponType].texture));
	mSprite.setOrigin(0.f, mSprite.getLocalBounds().height / 2.f);
	mSprite.setPosition(handOffset);
	// Przykładowy offset - dostosuj do swojego sprite'a
	//mHandOffset = sf::Vector2f(25.f, 0.f); // 25 pikseli na prawo od środka
	
	
	mFireCommand.category = Category::SceneAirLayer;	
	mFireCommand.action = [this, &textures](SceneNode& node, sf::Time)
	{
		createProjectile(node, Projectile::AR_Bullet, Projectile::AlliedBullet, textures);
	};

}

void Weapon::fire(CommandQueue& commands)
{
	if ((mCurrentAmmo > 0) && (mTimeSinceLastShot >= sf::seconds(1.f / mFireRate)) && !mIsReloading)
	{
		mCurrentAmmo--;
		mTimeSinceLastShot = sf::Time::Zero;
		commands.push(mFireCommand);
	}
}

void Weapon::reload()
{
	if (isReloading())
	{
		return;
	}

	if (mCurrentAmmo == mMagazineSize)
	{
		std::cout << "Magazynek jest pełny!" << std::endl;
		return;
	}

	if (mTotalAmmo == 0)
	{
		std::cout << "Brak amunicji w rezerwie!" << std::endl;
		return;
	}

	mIsReloading = true;
	mReloadTimer = sf::Time::Zero;
	std::cout << "Rozpoczynam przeładowanie..." << std::endl;
}

bool Weapon::isReloading() const
{
	return mIsReloading;
}

void Weapon::addAmmo(int ammo)
{
	mTotalAmmo += ammo;
}

int Weapon::getCurrentAmmo() const
{
	return mCurrentAmmo;
}

int Weapon::getTotalAmmo() const
{
	return mTotalAmmo;
}


void Weapon::update(sf::Time dt, CommandQueue& commands)
{
	mTimeSinceLastShot += dt;

	if (mIsReloading)
	{
		mReloadTimer += dt;
		if (mReloadTimer >= mReloadTime)
		{
			int ammoNeeded = mMagazineSize - mCurrentAmmo; 
			int ammoToTake = std::min(ammoNeeded, mTotalAmmo);
			mCurrentAmmo += ammoToTake; 
			mTotalAmmo -= ammoToTake;
			mIsReloading = false;
			mReloadTimer = sf::Time::Zero;
			std::cout << "Przeładowanie zakończone! Amunicja: "
				<< mCurrentAmmo << "/" << mMagazineSize
				<< ", Rezerwa: " << mTotalAmmo << std::endl;
		}
	}


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

void Weapon::createProjectile(SceneNode& node, Projectile::WeaponType weaponType, Projectile::Type type, const TextureHolder& textures) const
{
	std::unique_ptr<Projectile> projectile(new Projectile(weaponType, type, textures));

	sf::FloatRect bounds = mSprite.getGlobalBounds();
	float spriteWidth = bounds.width;
	float spriteHeight = bounds.height;

	sf::Vector2f barrelOffset(spriteWidth / 2.f, 0.f);
	float angleRad = std::atan2(mAimDirection.y, mAimDirection.x);

	sf::Vector2f rotatedOffset(
		barrelOffset.x * std::cos(angleRad) - barrelOffset.y * std::sin(angleRad),
		barrelOffset.x * std::sin(angleRad) + barrelOffset.y * std::cos(angleRad)
	);

	projectile->setPosition(getWorldPosition() + rotatedOffset);

	sf::Vector2f velocity = unitVector(mAimDirection) * projectile->getMaxSpeed();
	projectile->setVelocity(velocity);

	projectile->setRotation(angleRad * 180.f / 3.14159265f + 90.f);

	node.attachChild(std::move(projectile));
}

sf::Vector2f Weapon::getWorldPosition() const
{
	return mOwner ? (mOwner->getWorldPosition() + mSprite.getPosition()) : sf::Vector2f(0.f, 0.f);
}