#pragma once
#include "Entity.h"
#include "CharacterAnimation.h"

class Enemy : public Entity
{
	public:
	enum Direction
	{
		Up,
		Down,
		Left,
		Right,
	};

	Enemy(const TextureHolder& textures, CharacterAnimation::EntityType entityType);

	float getSpeed();
	virtual unsigned int getCategory() const override;

private:
	virtual void updateCurrent(sf::Time dt, CommandQueue& commands);
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
	void updateDirection();
	void updateAnimation(sf::Time dt);

private:
	CharacterAnimation mAnimation;
	float mSpeed;
	Direction mDirection;
};

