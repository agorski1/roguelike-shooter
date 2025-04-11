#pragma once
#include "DataTables.h"
#include "MapGenerator.h"
#include "TileMap.h"
#include "SceneNode.h"
#include <random>

struct LevelTable;
class EntityManager;


class LevelManager
{
public:
    LevelManager(MapGenerator& mapGenerator, TileMap& tileMap, EntityManager& entityManager, SceneNode& sceneGraph);

    void update(sf::Time dt);
    void checkLevelCompletion();
    void advanceToNextLevel();

    int getCurrentLevelIndex() const { return mCurrentLevelIndex; }
    bool isGameCompleted() const { return mCurrentLevelIndex >= 50; }
    void generateLevel();

private:
    MapGenerator& mMapGenerator;
    TileMap& mTileMap;
    EntityManager& mEntityManager;
    SceneNode& mSceneGraph;

    LevelTable& mLevelTable;
    int mCurrentLevelIndex;
    bool mLevelCompleted;
    std::mt19937 mRandom;
};