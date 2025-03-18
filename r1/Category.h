#pragma once

namespace Category
{
	enum Type
	{
		None = 0,
		SceneAirLayer = 1 << 0,
		PlayerCharacter = 1 << 1,
		Enemy = 1 << 2,
		Pickup = 1 << 3,
		PlayerProjectile = 1 << 4,
		EnemyProjectile = 1 << 5,
		ParticleSystem = 1 << 6,
		SoundEffect = 1 << 7,

		Projectile = PlayerProjectile | EnemyProjectile,
	};
}