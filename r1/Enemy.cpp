#include "Enemy.h"
#include "DataTables.h"

Enemy::Enemy(const TextureHolder& textures, CharacterAnimation::EntityType entityType)
	: Entity(100)
	, mSpeed(0.f)
	, mDirection(Direction::Down)
	, mAnimation(textures, entityType)
{
}

unsigned int Enemy::getCategory() const
{
	return Category::Enemy;
}


void Enemy::updateCurrent(sf::Time dt, CommandQueue& commands)
{
	updateDirection();
	updateAnimation(dt);
	Entity::updateCurrent(dt, commands);
}

void Enemy::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	Entity::drawCurrent(target, states);
}

void Enemy::updateAnimation(sf::Time dt)
{
	if (getVelocity().x == 0 && getVelocity().y == 0)
	{
		switch (mDirection)
		{
		case Up:    mAnimation.setAnimationType(AnimationType::IdleUp); break;
		case Down:  mAnimation.setAnimationType(AnimationType::IdleDown); break;
		case Left:  mAnimation.setAnimationType(AnimationType::IdleLeft); break;
		case Right: mAnimation.setAnimationType(AnimationType::IdleRight); break;
		}
	}
	else
	{
		switch (mDirection)
		{
		case Up:    mAnimation.setAnimationType(AnimationType::WalkUp); break;
		case Down:  mAnimation.setAnimationType(AnimationType::WalkDown); break;
		case Left:  mAnimation.setAnimationType(AnimationType::WalkLeft); break;
		case Right: mAnimation.setAnimationType(AnimationType::WalkRight); break;
		}
	}
	mAnimation.update(dt);
}

void Enemy::updateDirection()
{
	if (getVelocity().x > 0)
		mDirection = Direction::Right;
	else if (getVelocity().x < 0)
		mDirection = Direction::Left;
	else if (getVelocity().y > 0)
		mDirection = Direction::Down;
	else if (getVelocity().y < 0)
		mDirection = Direction::Up;
}