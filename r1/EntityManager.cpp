#include "EntityManager.h"

EntityManager::EntityManager(TextureHolder& textures, SceneNode* sceneGraph)
    : mTextures(textures)
    , mSceneGraph(sceneGraph)
{
}

void EntityManager::addEntity(SceneNode* entity)
{
    mEntities.push_back(entity);
}



void EntityManager::update(sf::Time dt, CommandQueue& commands)
{
    for (auto it = mEntities.begin(); it != mEntities.end();)
    {
        SceneNode* entity = *it;
        if (entity->isDestroyed())
        {
            if (mSceneGraph)
            {
                mSceneGraph->detachChild(*entity);
            }
            it = mEntities.erase(it);
        }
        else
        {
            entity->update(dt, commands);
            ++it;
        }
    }
}

int EntityManager::getEnemyCount() const
{
    int count = 0;
    for (const auto& entity : mEntities)
    {
        if (entity->getCategory() == Category::Enemy)
        {
            count++;
        }
    }
    return count;
}

PlayerCharacter* EntityManager::getPlayer() const
{
    for (const auto& entity : mEntities)
    {
        if (entity->getCategory() == Category::PlayerCharacter)
        {
            return dynamic_cast<PlayerCharacter*>(entity);
        }
    }
    return nullptr;
}