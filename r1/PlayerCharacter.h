#pragma once
#include "Entity.h"
#include "CharacterAnimation.h"
#include "Weapon.h"
#include "StatsObserver.h"


class PlayerCharacter : public Entity
{
public:
	enum Direction
	{
		Up,
		Down,
		Left,
		Right,
	};
	
	PlayerCharacter(const TextureHolder& textures, CharacterAnimation::EntityType entityType);

	float getSpeed();
	virtual unsigned int getCategory() const override;
	void aimAt(sf::Vector2f mouseWorldPosition);
	void fire(CommandQueue& commands);
	void reloadWeapon();
	void addStatsObserver(StatsObserver* observer);
	void removeStatsObserver(StatsObserver* observer);
	virtual sf::FloatRect getBoundingRect() const;

private:
	virtual void updateCurrent(sf::Time dt, CommandQueue& commands);
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
	void updateDirection();
	void updateAnimation(sf::Time dt);
	void notifyStatsObservers();


private:
	sf::Vector2f mHandPosition;
	float mSpeed;
	Direction mDirection;
	Direction mAimDirection;
	Direction mLastAimDirection;
	CharacterAnimation mAnimation;
	std::vector<StatsObserver*> mStatsObservers;
	int mMaxHitpoints;

	std::unique_ptr<Weapon> mWeapon;
};

