#include "CollisionSystem.h"
#include "PlayerCharacter.h"
#include "Enemy.h"
#include "Portal.h"
#include "TileMap.h"

namespace
{
    bool matchesCategories(SceneNode::Pair& pair, unsigned int type1, unsigned int type2)
    {
        unsigned int category1 = pair.first->getCategory();
        unsigned int category2 = pair.second->getCategory();

        return (category1 & type1 && category2 & type2) || (category1 & type2 && category2 & type1);
    }
}

void CollisionSystem::checkCollisions(SceneNode& sceneGraph, CommandQueue& commands)
{
    std::set<SceneNode::Pair> collisionPairs;
    sceneGraph.checkSceneCollision(sceneGraph, collisionPairs);

    for (SceneNode::Pair pair : collisionPairs)
    {
        if (matchesCategories(pair, Category::PlayerCharacter, Category::Portal))
        {
            Portal* portal = nullptr;

            if (pair.first->getCategory() & Category::Portal)
            {
                portal = dynamic_cast<Portal*>(pair.first);
            }
            else
            {
                portal = dynamic_cast<Portal*>(pair.second);
            }
            
            if (portal->isActive())
            {
                Command command;
                command.category = Category::TileMap;
                command.action = derivedAction<TileMap>([&](TileMap& tileMap, sf::Time)
			    {
				    tileMap.playerEnteredPortal();
			    }); 

                commands.push(command);

            }
        }
        else if (matchesCategories(pair, Category::PlayerCharacter, Category::Enemy))
        {
            auto& player = static_cast<PlayerCharacter&>(*pair.first);
            auto& enemy = static_cast<Enemy&>(*pair.second);

            player.damage(enemy.getHitpoints());
            enemy.destroy();
        }
    }
}