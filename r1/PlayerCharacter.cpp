#include "PlayerCharacter.h"
#include "Category.h"
#include "Utility.h"


PlayerCharacter::PlayerCharacter(const TextureHolder& textures, CharacterAnimation::EntityType entityType)
    : Entity(3)
    , mSpeed(1000.f)
    , mDirection(Down)
    , mAimDirection(Down)
    , mLastAimDirection(Down)
    , mWeapon(nullptr)
    , mAnimation(textures, entityType)
    , mHandPosition(-18.f, 14.f)
    , mStatsObservers()
    , mMaxHitpoints(5)
{
    mWeapon = std::make_unique<Weapon>(Weapon::AssaultRifle, textures, this, mHandPosition);
    centerOrigin(mAnimation);
}

float PlayerCharacter::getSpeed()
{
    return mSpeed;
}

unsigned int PlayerCharacter::getCategory() const
{
    return Category::PlayerCharacter;
}

void PlayerCharacter::aimAt(sf::Vector2f mouseWorldPosition)
{
    sf::Vector2f direction = mouseWorldPosition - getPosition();

    if (std::abs(direction.x) > std::abs(direction.y))
    {
        mAimDirection = (direction.x > 0) ? Right : Left;
    }
    else
    {
        mAimDirection = (direction.y > 0) ? Down : Up;
    }

    if (mWeapon)
    {
        mWeapon->setAimDirection(direction);
    }
}

void PlayerCharacter::fire(CommandQueue& commands)
{
    if (mWeapon)
	{
		mWeapon->fire(commands);
	}
}

void PlayerCharacter::reloadWeapon()
{
    if (mWeapon)
	{
		mWeapon->reload();
	}
}

void PlayerCharacter::addStatsObserver(StatsObserver* observer)
{
	mStatsObservers.push_back(observer);
}

void PlayerCharacter::removeStatsObserver(StatsObserver* observer)
{
    mStatsObservers.erase(std::remove(mStatsObservers.begin(), mStatsObservers.end(), observer), mStatsObservers.end());
}

void PlayerCharacter::updateCurrent(sf::Time dt, CommandQueue& commands)
{
    Entity::updateCurrent(dt, commands);
    updateDirection();
    updateAnimation(dt);
    if (mWeapon)
    {
        mWeapon->update(dt, commands);
    }

    notifyStatsObservers();
}

void PlayerCharacter::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(mAnimation, states);
    if (mWeapon)
    {
        mWeapon->draw(target, states);
    }
}

void PlayerCharacter::updateAnimation(sf::Time dt)
{
    // Wybierz typ animacji
    if (getVelocity().x == 0 && getVelocity().y == 0)
    {
        switch (mAimDirection)
        {
        case Up:    mAnimation.setAnimationType(AnimationType::IdleUp); break;
        case Down:  mAnimation.setAnimationType(AnimationType::IdleDown); break;
        case Left:  mAnimation.setAnimationType(AnimationType::IdleLeft); break;
        case Right: mAnimation.setAnimationType(AnimationType::IdleRight); break;
        }
    }
    else
    {
        switch (mAimDirection)
        {
        case Up:    mAnimation.setAnimationType(AnimationType::WalkUp); break;
        case Down:  mAnimation.setAnimationType(AnimationType::WalkDown); break;
        case Left:  mAnimation.setAnimationType(AnimationType::WalkLeft); break;
        case Right: mAnimation.setAnimationType(AnimationType::WalkRight); break;
        }
    }

    // Jeśli kierunek celowania się zmienił, zresetuj animację
    if (mAimDirection != mLastAimDirection)
    {
        mAnimation.restart(); // Zakładamy, że Animation ma metodę reset()
        mLastAimDirection = mAimDirection;
    }

    mAnimation.update(dt);
}

void PlayerCharacter::notifyStatsObservers()
{
    PlayerStats stats;
    stats.hp = getHitpoints();
    stats.speed = mSpeed;
    stats.maxHp = mMaxHitpoints;
    if (mWeapon)
    {
        stats.currentAmmo = mWeapon->getCurrentAmmo();
        stats.totalAmmo = mWeapon->getTotalAmmo();
    }
    else
    {
        stats.currentAmmo = 0;
        stats.totalAmmo = 0;
    }

    for (StatsObserver* observer : mStatsObservers)
    {
        observer->onStatsUpdated(stats);
    }
}

sf::FloatRect PlayerCharacter::getBoundingRect() const
{
    return getWorldTransform().transformRect(mAnimation.getGlobalBounds());
}


void PlayerCharacter::updateDirection()
{
    if (getVelocity().x > 0)
        mDirection = Right;
    else if (getVelocity().x < 0)
        mDirection = Left;
    else if (getVelocity().y > 0)
        mDirection = Down;
    else if (getVelocity().y < 0)
        mDirection = Up;
}
