#pragma once
#include "Entity.h"
#include "Animation.h"

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

	Enemy(const TextureHolder& textures, Animation::EntityType entityType);

	float getSpeed();
	virtual unsigned int getCategory() const override;

private:
	virtual void updateCurrent(sf::Time dt, CommandQueue& commands);
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
	void updateDirection();
	virtual void updateAnimation(sf::Time dt) override;

private:
	float mSpeed;
	Direction mDirection;
};

