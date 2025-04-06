#pragma once
#include "SFML/System/Vector2.hpp"
#include "SFML//System/Time.hpp"

#include "CharacterAnimation.h"
#include "Weapon.h"
#include "ResourceIdentifiers.h"

#include "Projectile.h"


#include <vector>
#include <map>


struct AnimationData
{
    Textures::ID texture;
    sf::Vector2i frameSize;
    sf::Time duration;
    bool repeat;
    std::unordered_map<AnimationType, int> frameCounts;
};

struct WeaponData
{
    int magazineSize;
    int totalAmmo;
    sf::Time reloadTime;
    float fireRate;
    Textures::ID texture;
};

struct ProjectileData
{
    int damage;
    float speed;
    Textures::ID texture;
};

struct MapGenerationParams
{
    int numWalkers;
    int stepsPerWalker;
    float changeDirectionChance;
    int walkerEatSize;
    float addWallChance;
    float removeWallChance;
    float destructibleWallChance;
    float trapChance;
};


struct LevelTextures
{
    Textures::ID floor;
    Textures::ID wall;
    Textures::ID destructibleWall;
    Textures::ID trap;
};

struct LevelData
{
    std::string levelName;
    MapGenerationParams mapParams;
    LevelTextures levelTextures;
};

struct LevelTable
{
    std::vector<LevelData> regularLevels;
    std::vector<LevelData> bossLevels;
};

std::vector<AnimationData> initializeAnimationData();
std::vector<WeaponData> initializeWeaponData();
std::vector<ProjectileData> initializeProjectileData();
LevelTable initializeLevelData();
