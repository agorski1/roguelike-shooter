#pragma once
#include "SceneNode.h"
#include "CommandQueue.h"

class CollisionSystem
{
public:
    void checkCollisions(SceneNode& sceneGraph, CommandQueue& commands);
};