#include "World.h"
#include <algorithm>
#include <cmath>
#include <iostream>
#include "SoundPlayer.h"
#include "SpriteNode.h"
#include "PlayerCharacter.h"
#include "TileMap.h"


World::World(sf::RenderTarget& outputTarget, FontHolder& fonts, SoundPlayer& sounds)
	: mTarget(outputTarget)
	, mSceneTexture()
	, mWorldView(outputTarget.getDefaultView())
	, mTextures()
	, mFonts(fonts)
	, mSounds(sounds)
	, mSceneGraph()
	, mSceneLayers()
	, mWorldBounds(
		0.f,						// left x position
		0.f,						// top y position
		mWorldView.getSize().x,		// width
		2000.f)						// height
	, mSpawnPosition(
		mWorldView.getSize().x / 2.f,
		mWorldBounds.height - mWorldView.getSize().y / 2.f)
	, mPlayerCharacter(nullptr)
	, mTileMap(nullptr)
	, mEntityManager(mTextures, &mSceneGraph)
	, mMapGenerator(50, 50)
	, mLevelManager(nullptr)
	, mCollisionSystem()
{
	mSceneTexture.create(mTarget.getSize().x, mTarget.getSize().y);

	loadTextures();
	buildScene();

	mWorldView.setCenter(mSpawnPosition);
}

void World::update(sf::Time dt, sf::Vector2f mouseWorldPos)
{
	mWorldView.setCenter(mPlayerCharacter->getPosition());
	mMouseWorldPosition = mouseWorldPos;
	mPlayerCharacter->setVelocity(0.f, 0.f);

	while (!mCommandQueue.isEmpty())
		mSceneGraph.onCommand(mCommandQueue.pop(), dt);

	mLevelManager->update(dt);
	mEntityManager.update(dt, mCommandQueue);
	mSceneGraph.update(dt, mCommandQueue);

	mCollisionSystem.checkCollisions(mSceneGraph, mCommandQueue);

	adaptPlayerPosition();

	//updateSounds();
}

void World::draw()
{
	mTarget.setView(mWorldView);
	mTarget.draw(mSceneGraph);
}

void World::setMousePosition(sf::Vector2i pixelPosition)
{
	mMouseWorldPosition = mTarget.mapPixelToCoords(pixelPosition, mWorldView);
}

sf::Vector2f World::getMouseWorldPosition() const
{
	return mMouseWorldPosition;
}


CommandQueue& World::getCommandQueue()
{
	return mCommandQueue;
}

PlayerCharacter* World::getPlayerCharacter()
{
	return mPlayerCharacter;
}

void World::loadTextures()
{
	mTextures.load(Textures::MainCharacter, "assets/textures/character.png");
	mTextures.load(Textures::Ak47, "assets/textures/ak.png");	
	mTextures.load(Textures::Bullet, "assets/textures/Bullet.png");
	mTextures.load(Textures::WallBrick, "assets/textures/brick_floor.png");
	mTextures.load(Textures::FloorBrick, "assets/textures/brick_wall.png");
	mTextures.load(Textures::FloorIndustrial, "assets/textures/industrial_floor.png");
	mTextures.load(Textures::WallIndustrial, "assets/textures/industrial_wall.png");
	mTextures.load(Textures::FloorUrban1, "assets/textures/urban1_floor.png");
	mTextures.load(Textures::WallUrban1, "assets/textures/urban1_wall.png");
	mTextures.load(Textures::FloorUrban2, "assets/textures/urban2_floor.png");
	mTextures.load(Textures::WallUrban2, "assets/textures/urban2_wall.png");
	mTextures.load(Textures::DestructibleWall, "assets/textures/destructiblewall.png");
	mTextures.load(Textures::Trap, "assets/textures/trap.png");
	mTextures.load(Textures::Portal, "assets/textures/portal.png");

}

void World::buildScene()
{
	for (size_t i = 0; i < LayerCount; ++i)
	{
		Category::Type category = (i == LowerAir) ? Category::SceneAirLayer : Category::None;

		SceneNode::Ptr layer(new SceneNode(category));
		mSceneLayers[i] = layer.get(); // returns raw pointer 

		mSceneGraph.attachChild(std::move(layer));
	}

	// TileMap
	std::unique_ptr<TileMap> tileMap(new TileMap(mTextures));
	mTileMap = tileMap.get();
	mSceneLayers[LowerAir]->attachChild(std::move(tileMap));

	// PlayerCharacter
	std::unique_ptr<PlayerCharacter> player(new PlayerCharacter(mTextures, CharacterAnimation::Player));
	mPlayerCharacter = player.get();
	mPlayerCharacter->setPosition(mSpawnPosition);
	mSceneLayers[UpperAir]->attachChild(std::move(player));


	// Inicjalizacja LevelManager po utworzeniu mTileMap
	mLevelManager = std::make_unique<LevelManager>(mMapGenerator, *mTileMap, mEntityManager, mSceneGraph);
	mLevelManager->generateLevel();

}

void World::adaptPlayerPosition()
{
	
}

const sf::View& World::getWorldView() const 
{ 
	return mWorldView; 
}


sf::FloatRect World::getViewBounds() const
{
	return sf::FloatRect(mWorldView.getCenter() - mWorldView.getSize() / 2.f, mWorldView.getSize());
}

sf::FloatRect World::getBattlefieldBounds() const
{
	sf::FloatRect bounds = getViewBounds();
	bounds.top -= 100.f;
	bounds.height += 100.f;

	return bounds;
}

//void World::updateSounds()
//{
//	mSounds.setListenerPosition(mPlayerAircraft->getWorldPosition());
//	mSounds.removeStoppedSounds();
//}



