#include "DataTables.h"

std::vector<AnimationData> initializeAnimationData()
{
    std::vector<AnimationData> data(CharacterAnimation::EntityCount);

    data[CharacterAnimation::Player].texture = Textures::MainCharacter;
    data[CharacterAnimation::Player].frameSize = { 128, 128 };
    data[CharacterAnimation::Player].duration = sf::seconds(1);
    data[CharacterAnimation::Player].repeat = true;
    
    data[CharacterAnimation::Player].frameCounts[AnimationType::IdleUp] = 2;
    data[CharacterAnimation::Player].frameCounts[AnimationType::IdleDown] = 2;
    data[CharacterAnimation::Player].frameCounts[AnimationType::IdleLeft] = 2;
    data[CharacterAnimation::Player].frameCounts[AnimationType::IdleRight] = 2;


    data[CharacterAnimation::Player].frameCounts[AnimationType::WalkUp] = 9;
    data[CharacterAnimation::Player].frameCounts[AnimationType::WalkDown] = 9;
    data[CharacterAnimation::Player].frameCounts[AnimationType::WalkLeft] = 9;
    data[CharacterAnimation::Player].frameCounts[AnimationType::WalkRight] = 9;

    data[CharacterAnimation::Player].frameCounts[AnimationType::Dash] = 4;

    return data;
}

std::vector<WeaponData> initializeWeaponData()
{
    std::vector<WeaponData> data(Weapon::WeaponCount);

    data[Weapon::AssaultRifle] = { 30, 300, sf::seconds(2.5f), 20.f, Textures::Ak47 };

    return data;
}

std::vector<ProjectileData> initializeProjectileData()
{
    std::vector<ProjectileData> data(Projectile::TypeCount);

    data[Projectile::AR_Bullet] = { 1, 1000.f, Textures::Bullet };


    return data;
}

LevelTable initializeLevelData()
{
    LevelTable table;

    std::vector<LevelData> regularLevels;

    {
        LevelData brick;
        brick.levelName = "Brick";
        brick.levelTextures = {
            Textures::FloorBrick,
            Textures::WallBrick,
            Textures::DestructibleWall, 
            Textures::Trap
        };
        brick.mapParams = {
            3,      // numWalkers
            150,    // stepsPerWalker
            0.1f,   // changeDirectionChance
            1,      // walkerEatSize
            0.1f,   // addWallChance
            0.4f,   // removeWallChance
            0.05f,  // destructibleWallChance
            0.1f    // trapChance
        };
        regularLevels.push_back(brick);
    }

    {
        LevelData industrial;
        industrial.levelName = "Industrial";
        industrial.levelTextures = {
            Textures::FloorIndustrial,
            Textures::WallIndustrial,
            Textures::DestructibleWall,
            Textures::Trap
        };
        industrial.mapParams = {
            4,
            200,
            0.4f,
            0,
            0.3f,
            0.1f,
            0.15f,
            0.05f
        };
        regularLevels.push_back(industrial);
    }

    {
        LevelData urban1;
        urban1.levelName = "Urban 1";
        urban1.levelTextures = {
            Textures::FloorUrban1,
            Textures::WallUrban1,
            Textures::DestructibleWall,
            Textures::Trap
        };
        urban1.mapParams = {
            2,
            250,
            0.6f,
            4,
            0.4f,
            0.05f,
            0.1f,
            0.1f
        };
        regularLevels.push_back(urban1);
    }

    // Poziom Urban 2
    {
        LevelData urban2;
        urban2.levelName = "Urban 2";
        urban2.levelTextures = {
            Textures::FloorUrban2,
            Textures::WallUrban2,
            Textures::DestructibleWall,
            Textures::Trap
        };
        urban2.mapParams = {
            5,
            100,
            0.2f,
            2,
            0.05f,
            0.5f,
            0.05f,
            0.1f
        };
        regularLevels.push_back(urban2);
    }

    std::vector<LevelData> bossLevels;

    {
        LevelData brickBoss;
        brickBoss.levelName = "Brick Boss Arena";
        brickBoss.levelTextures = {
            Textures::FloorBrick,
            Textures::WallBrick,
            Textures::DestructibleWall,
            Textures::Trap
        };
        brickBoss.mapParams = {
            2,      
            50,     
            0.2f,  
            1,    
            0.05f,  
            0.1f,
            0.1f,
            0.15f
        };
        bossLevels.push_back(brickBoss);
    }

    {
        LevelData industrialBoss;
        industrialBoss.levelName = "Industrial Boss Arena";
        industrialBoss.levelTextures = {
            Textures::FloorIndustrial,
            Textures::WallIndustrial,
            Textures::DestructibleWall,
            Textures::Trap
        };
        industrialBoss.mapParams = {
            3,
            60,
            0.15f,
            1,
            0.03f,
            0.05f,
            0.05f,
            0.2f
        };
        bossLevels.push_back(industrialBoss);
    }

    {
        LevelData urban1Boss;
        urban1Boss.levelName = "Urban 1 Boss Arena";
        urban1Boss.levelTextures = {
            Textures::FloorUrban1,
            Textures::WallUrban1,
            Textures::DestructibleWall,
            Textures::Trap
        };
        urban1Boss.mapParams = {
            2,
            55,
            0.25f,
            1,
            0.07f,
            0.02f,
            0.08f,
            0.18f
        };
        bossLevels.push_back(urban1Boss);
    }

    {
        LevelData urban2Boss;
        urban2Boss.levelName = "Urban 2 Boss Arena";
        urban2Boss.levelTextures = {
            Textures::FloorUrban2,
            Textures::WallUrban2,
            Textures::DestructibleWall,
            Textures::Trap
        };
        urban2Boss.mapParams = {
            3,
            50,
            0.3f,
            1,
            0.05f,
            0.03f,
            0.1f,
            0.15f
        };
        bossLevels.push_back(urban2Boss);
    }

    table.regularLevels = regularLevels;
    table.bossLevels = bossLevels;
    return table;
}
