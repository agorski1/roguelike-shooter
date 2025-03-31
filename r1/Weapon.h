#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Texture.hpp>
#include "ResourceIdentifiers.h"

class CommandQueue;

class Weapon : public sf::Transformable, public sf::Drawable
{
public:
	enum WeaponType
	{
		Blaster,
		Spread,
		Phaser,
		Missile,
		AssaultRifle,
		WeaponCount
	};

	explicit Weapon(WeaponType weaponType, const TextureHolder& textures);
	void fire(CommandQueue& commands);
	void reload();
	bool isReloading() const;
	void setAmmo(int ammo);
	int getAmmo() const;


	void update(sf::Time dt, CommandQueue& commands);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void setAimDirection(sf::Vector2f direction);

private:
	WeaponType mWeaponType;
	sf::Sprite mSprite;
	int mMagazineSize;
	int mCurrentAmmo;
	int mTotalAmmo;
	sf::Time mReloadTime;
	float mFireRate;
	sf::Time mTimeSinceLastShot;
	sf::Vector2f mAimDirection;
	bool mIsFlipped = false;
};

