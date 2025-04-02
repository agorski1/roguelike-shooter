#pragma once
#include "Entity.h"
#include "SFML/Graphics/Sprite.hpp"

class CommandQueue;

class Projectile : public Entity
{
public:
	enum Type
	{
		AlliedBullet,
		EnemyBullet,
	};

	enum WeaponType
	{
		AR_Bullet,
		Laser,
		Missile,
		ShotgunPellet,
		TypeCount
	};

	Projectile(WeaponType weaponType, Type type, const TextureHolder& textures);

	void guideTowards(sf::Vector2f position);
	bool isGuided() const;
	virtual unsigned int getCategory() const;
	virtual sf::FloatRect getBoundingRect() const;
	float getMaxSpeed() const;
	int getDamage() const;

private:
	virtual void updateCurrent(sf::Time dt, CommandQueue& commands);
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	Type mType;
	WeaponType mWeaponType;
	sf::Sprite mSprite;
	sf::Vector2f mTargetDirection;
};

