#include "LevelManager.h"
#include "DataTables.h"
#include "EntityManager.h"

namespace 
{
    LevelTable levelTable = initializeLevelData();
}


LevelManager::LevelManager(MapGenerator& mapGenerator, TileMap& tileMap, EntityManager& entityManager, SceneNode& sceneGraph)
    : mMapGenerator(mapGenerator)
    , mTileMap(tileMap)
    , mEntityManager(entityManager)
    , mSceneGraph(sceneGraph)
    , mCurrentLevelIndex(0)
    , mLevelCompleted(false)
    , mRandom(static_cast<unsigned>(std::time(nullptr)))
    , mLevelTable(levelTable)
{
}



void LevelManager::generateLevel()
{
    std::cout << "Generating level " << mCurrentLevelIndex + 1 << std::endl;
    bool isBossLevel = (mCurrentLevelIndex + 1) % 10 == 0;

    LevelData levelData;
    if (isBossLevel)
    {
        std::uniform_int_distribution<> dis(0, mLevelTable.bossLevels.size() - 1);
        levelData = mLevelTable.bossLevels[dis(mRandom)];
    }
    else
    {
        std::uniform_int_distribution<> dis(0, mLevelTable.regularLevels.size() - 1);
        levelData = mLevelTable.regularLevels[dis(mRandom)];
    }

    mMapGenerator.generateLevel(levelData);
    mTileMap.load(mMapGenerator.getMap(), levelData.levelTextures);
    //mEntityManager.spawnEntities(mTileMap, isBossLevel);
}

void LevelManager::update(sf::Time dt)
{
    if (!mLevelCompleted)
    {
        checkLevelCompletion();
    }

    if (mTileMap.hasPlayerEnteredPortal())
    {
        advanceToNextLevel();
        mTileMap.resetPlayerEnteredPortal();
    }
}

void LevelManager::checkLevelCompletion()
{   
    if (mEntityManager.getEnemyCount() == 0)
    {
        mLevelCompleted = true;
        std::cout << "portal" << std::endl;
        mTileMap.spawnPortal();
    }
}

void LevelManager::advanceToNextLevel()
{
    if (isGameCompleted())
    {
        return;
    }

    mCurrentLevelIndex++;
    mLevelCompleted = false;


    // watek i stan loading next level
    generateLevel();
}