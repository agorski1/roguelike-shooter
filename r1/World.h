#pragma once
#include <SFML/Graphics.hpp>
#include "ResourceIdentifiers.h"
#include "SceneNode.h"
#include <array>
#include "CommandQueue.h"
#include <vector>
#include "ResourceHolder.h"

#include "EntityManager.h"
#include "MapGenerator.h"
#include "LevelManager.h"	
#include "CollisionSystem.h"


class TileMap;
class SoundPlayer;
class PlayerCharacter;

class World : public sf::NonCopyable
{
public:
	explicit World(sf::RenderTarget& outputTarget, FontHolder& fonts, SoundPlayer& sounds);
	void update(sf::Time dt, sf::Vector2f mouseWorldPos);
	void draw();
	void setMousePosition(sf::Vector2i pixelPosition);
	sf::Vector2f getMouseWorldPosition() const;
	const sf::View& getWorldView() const;
	CommandQueue& getCommandQueue();

	PlayerCharacter* getPlayerCharacter();

private:
	void loadTextures();
	void buildScene();

	void adaptPlayerPosition();
	//void adaptPlayerVelocity();

	sf::FloatRect getViewBounds() const;
	sf::FloatRect getBattlefieldBounds() const;

	//void updateSounds();

private:
	enum Layer
	{
		Background,
		LowerAir,
		UpperAir,
		LayerCount
	};

	/*struct SpawnPoint
	{
		SpawnPoint(Aircraft::Type type, float x, float y)
			: type(type)
			, x(x)
			, y(y)
		{
		}

		Aircraft::Type type;
		float x;
		float y;
	};*/

private:
	sf::RenderTarget& mTarget;
	sf::RenderTexture mSceneTexture;
	sf::View mWorldView;
	TextureHolder mTextures;
	FontHolder& mFonts;
	SoundPlayer& mSounds;
	sf::Vector2f mMouseWorldPosition;


	SceneNode mSceneGraph;
	std::array<SceneNode*, LayerCount> mSceneLayers;
	sf::FloatRect mWorldBounds;
	sf::Vector2f mSpawnPosition;
	PlayerCharacter* mPlayerCharacter;
	CommandQueue mCommandQueue;

	TileMap* mTileMap;
	EntityManager mEntityManager;
	MapGenerator mMapGenerator;
	std::unique_ptr<LevelManager> mLevelManager;
	CollisionSystem mCollisionSystem;

};


