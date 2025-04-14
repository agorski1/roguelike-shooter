#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <random>
#include "TileMap.h"
#include "DataTables.h"

class MapGenerator
{
public:
    MapGenerator(int width, int height);
    void generateLevel(const LevelData& levelData);
    const std::vector<std::vector<Tile>>& getMap() const { return mMap; }

private:
    void initializeMap();
    void runWalker(sf::Vector2i startPos, int steps, const MapGenerationParams& params);
    void modifyMap(const MapGenerationParams& params);
    void addDetails(const MapGenerationParams& params);

    int mWidth;
    int mHeight;
    std::vector<std::vector<Tile>> mMap;
    std::mt19937 mRandom;
};