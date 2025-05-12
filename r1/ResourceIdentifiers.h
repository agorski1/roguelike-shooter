#ifndef TEXTURES_ID_HPP 
#define TEXTURES_ID_HPP

#include "ResourceHolder.h"

namespace sf
{
	class Texture;
	class Font;
	class Shader;
	class SoundBuffer;
}



namespace Textures
{
	enum ID
	{
		Entities,
		Jungle,
		TitleScreen,
		Buttons,
		Explosion,
		Particle,
		FinishLine,
		Brick,
		Crosshair,
		MainCharacter,
		Ak47,
		Bullet,
		FloorBrick,
		WallBrick,
		FloorIndustrial,
		WallIndustrial,
		FloorUrban1,
		WallUrban1,
		FloorUrban2,
		WallUrban2,
		Portal,
		DestructibleWall,
		Trap,
		
	};
}


namespace Shaders
{
	enum ID
	{
		BrightnessPass,
		DownSamplePass,
		GaussianBlurPass,
		AddPass,
	};
}

namespace Fonts
{
	enum ID
	{
		Main,
		Stats,
	};
}

namespace SoundEffect
{
	enum ID
	{
		AlliedGunfire,
		EnemyGunfire,
		Explosion1,
		Explosion2,
		LaunchMissile,
		CollectPickup,
		Button,
	};
}

namespace Music
{
	enum ID
	{
		MenuTheme,
		MissionTheme,
	};
}

template <typename Resource, typename Identifier>
class ResourceHolder;

typedef ResourceHolder<sf::Texture, Textures::ID> TextureHolder;
typedef ResourceHolder<sf::Font, Fonts::ID> FontHolder;
typedef ResourceHolder<sf::Shader, Shaders::ID> ShaderHolder;
typedef ResourceHolder<sf::SoundBuffer, SoundEffect::ID> SoundBufferHolder;
#endif // !TEXTURES_ID_HPP 



