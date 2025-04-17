#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Texture.hpp>
#include "ResourceIdentifiers.h"
#include "Projectile.h"
#include "Command.h"

class PlayerCharacter;
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

	explicit Weapon(WeaponType weaponType, const TextureHolder& textures, PlayerCharacter* owner, sf::Vector2f handOffset);
	void fire(CommandQueue& commands);
	void reload();
	bool isReloading() const;

	void addAmmo(int ammo);
	int getCurrentAmmo() const;
	int getTotalAmmo() const;

	void update(sf::Time dt, CommandQueue& commands);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void setAimDirection(sf::Vector2f direction);

private:
	void createProjectile(SceneNode& node, Projectile::WeaponType weaponType, Projectile::Type type, const TextureHolder& textures) const;
	sf::Vector2f getWorldPosition() const;
private:
	PlayerCharacter* mOwner;	

	Command mFireCommand;

	WeaponType mWeaponType;
	sf::Sprite mSprite;
	int mMagazineSize;
	int mCurrentAmmo;
	int mTotalAmmo;
	sf::Time mReloadTime;
	sf::Time mReloadTimer;
	float mFireRate;
	sf::Time mTimeSinceLastShot;
	sf::Vector2f mAimDirection;
	bool mIsFlipped = false;
	bool mIsReloading = false;
};

