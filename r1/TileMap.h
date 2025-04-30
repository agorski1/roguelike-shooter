#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "ResourceHolder.h"
#include "ResourceIdentifiers.h"
#include "SceneNode.h"
#include "Portal.h"
#include <random>
#include "Tile.h"

struct LevelTextures;



class TileMap : public SceneNode
{
public:
    TileMap(TextureHolder& textures);
    void load(const std::vector<std::vector<Tile>>& map, const LevelTextures& textures);
    const std::vector<std::vector<Tile>>& getMap() const { return mMap; }
    void setTile(int x, int y, TileType type);
    void spawnPortal(); 
    void clearPortal(); 

    bool hasPlayerEnteredPortal() const;
    void resetPlayerEnteredPortal();
    void playerEnteredPortal();
    
    virtual unsigned int getCategory() const override;

private:
    void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;
    void updateCurrent(sf::Time dt, CommandQueue& commands) override;

private:
    TextureHolder& mTextures;
    std::vector<std::vector<Tile>> mMap;
    std::vector<sf::Sprite> mSprites;
    sf::Vector2f mTileSize;
    std::unique_ptr<Portal> mPortal;
    std::mt19937 mRandom; 
    bool mPlayerEnteredPortal;
};