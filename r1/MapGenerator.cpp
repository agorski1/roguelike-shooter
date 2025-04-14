#include "MapGenerator.h"
#include <ctime>
#include "DataTables.h"


MapGenerator::MapGenerator(int width, int height)
    : mWidth(width)
    , mHeight(height)
    , mMap(height, std::vector<Tile>(width))
    , mRandom(static_cast<unsigned>(time(nullptr)))
{
}

void MapGenerator::initializeMap()
{
    for (int y = 0; y < mHeight; ++y)
    {
        for (int x = 0; x < mWidth; ++x)
        {
            mMap[y][x].type = TileType::Wall;
            mMap[y][x].trapType = TrapType::None;
        }
    }
}

void MapGenerator::runWalker(sf::Vector2i startPos, int steps, const MapGenerationParams& params)
{
    sf::Vector2i pos = startPos;
    std::vector<sf::Vector2i> directions = {
        {0, -1}, {0, 1}, {-1, 0}, {1, 0}
    };

    sf::Vector2i lastDir = { 0, 0 };

    for (int i = 0; i < steps; ++i)
    {
        if (pos.x >= 0 && pos.x < mWidth && pos.y >= 0 && pos.y < mHeight)
        {
            mMap[pos.y][pos.x].type = TileType::Floor;
        }

        int eatSize = params.walkerEatSize;
        for (int dy = -eatSize; dy <= eatSize; ++dy)
        {
            for (int dx = -eatSize; dx <= eatSize; ++dx)
            {
                int newX = pos.x + dx;
                int newY = pos.y + dy;
                if (newX >= 0 && newX < mWidth && newY >= 0 && newY < mHeight)
                {
                    mMap[newY][newX].type = TileType::Floor;
                }
            }
        }

        std::uniform_int_distribution<int> dist(0, directions.size() - 1);
        sf::Vector2i dir = directions[dist(mRandom)];

        std::uniform_real_distribution<float> chanceDist(0.0f, 1.0f);
        if (chanceDist(mRandom) < params.changeDirectionChance)
        {
            dir = directions[dist(mRandom)];
            lastDir = dir;
        }
        else
        {
            dir = lastDir;
        }

        pos += dir;
    }
}

void MapGenerator::modifyMap(const MapGenerationParams& params)
{
    for (int y = 0; y < mHeight; ++y)
    {
        for (int x = 0; x < mWidth; ++x)
        {
            std::uniform_real_distribution<float> chanceDist(0.0f, 1.0f);
            if (mMap[y][x].type == TileType::Floor && chanceDist(mRandom) < params.addWallChance)
            {
                mMap[y][x].type = TileType::Wall;
            }
            if (mMap[y][x].type == TileType::Wall && chanceDist(mRandom) < params.removeWallChance)
            {
                mMap[y][x].type = TileType::Floor;
            }
        }
    }
}

void MapGenerator::addDetails(const MapGenerationParams& params)
{
    for (int y = 0; y < mHeight; ++y)
    {
        for (int x = 0; x < mWidth; ++x)
        {
            std::uniform_real_distribution<float> chanceDist(0.0f, 1.0f);
            if (mMap[y][x].type == TileType::Wall && chanceDist(mRandom) < params.destructibleWallChance)
            {
                mMap[y][x].type = TileType::DestructibleWall;
            }
            if (mMap[y][x].type == TileType::Floor && chanceDist(mRandom) < params.trapChance)
            {
                mMap[y][x].trapType = TrapType::Spikes;
            }
        }
    }
}

void MapGenerator::generateLevel(const LevelData& levelData)
{
    initializeMap();
    for (int i = 0; i < levelData.mapParams.numWalkers; ++i)
    {
        std::uniform_int_distribution<int> distX(0, mWidth - 1);
        std::uniform_int_distribution<int> distY(0, mHeight - 1);
        sf::Vector2i startPos(distX(mRandom), distY(mRandom));
        runWalker(startPos, levelData.mapParams.stepsPerWalker, levelData.mapParams);
    }
    modifyMap(levelData.mapParams);
    addDetails(levelData.mapParams);
}