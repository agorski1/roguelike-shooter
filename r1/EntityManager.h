#pragma once
#include "SceneNode.h"
#include "TileMap.h"
#include "Enemy.h"
#include "PlayerCharacter.h"
#include <vector>

class EntityManager
{
public:
    EntityManager(TextureHolder& textures, SceneNode* sceneGraph);
    void addEntity(SceneNode* entity);
    //void spawnEntities(TileMap& tileMap, bool isBossLevel, SceneNode& sceneGraph);
    void update(sf::Time dt, CommandQueue& commands);
    int getEnemyCount() const;
    PlayerCharacter* getPlayer() const;
    const std::vector<SceneNode*>& getEntities() const { return mEntities; }

private:
    std::vector<SceneNode*> mEntities;
    TextureHolder& mTextures;
    SceneNode* mSceneGraph; 
};
