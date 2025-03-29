#include "Entity.h"
#include <cassert>
#include <iostream>
#include "Utility.h"

Entity::Entity(int hitpoints, const TextureHolder& textures, Animation::EntityType entityType)
	: mVelocity()
	, mHitpoints(hitpoints)
	, mAnimation(textures, entityType)
{
	centerOrigin(mAnimation);
}


void Entity::damage(int points)
{
	assert(points > 0);

	mHitpoints -= points;
}

void Entity::destroy()
{
	mHitpoints = 0;
}

void Entity::remove()
{
	destroy();
}

int Entity::getHitpoints() const
{
	return mHitpoints;
}

bool Entity::isDestroyed() const
{
	return mHitpoints <= 0;
}

void Entity::setVelocity(sf::Vector2f velocity)
{
	mVelocity = velocity;
}

void Entity::setVelocity(float vx, float vy)
{
	mVelocity.x = vx;
	mVelocity.y = vy;
}

void Entity::accelerate(sf::Vector2f velocity)
{
	mVelocity += velocity;
}

void Entity::accelerate(float vx, float vy)
{
	mVelocity.x += vx;
	mVelocity.y += vy;
}

sf::Vector2f Entity::getVelocity() const
{
	return mVelocity;
}

void Entity::updateCurrent(sf::Time dt, CommandQueue& commands)
{
	mAnimation.update(dt);
	move(mVelocity * dt.asSeconds());
}

void Entity::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(mAnimation, states);
}

void Entity::setAnimationType(AnimationType type)
{
	mAnimation.setAnimationType(type);
}


