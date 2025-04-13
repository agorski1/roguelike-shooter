#include "TileMap.h"
#include "DataTables.h"

TileMap::TileMap(TextureHolder& textures)
    : mTextures(textures)
    , mTileSize(64.f, 64.f)
    , mPortal(nullptr)
    , mRandom(static_cast<unsigned>(std::time(nullptr)))
    , mPlayerEnteredPortal(false)
{
}

void TileMap::load(const std::vector<std::vector<Tile>>& map, const LevelTextures& textures)
{
    mMap = map;
    mSprites.clear();
    clearPortal(); 

    for (int y = 0; y < mMap.size(); ++y)
    {
        for (int x = 0; x < mMap[y].size(); ++x)
        {
            sf::Sprite sprite;
            sprite.setPosition(x * mTileSize.x, y * mTileSize.y);

            switch (mMap[y][x].type)
            {
            case TileType::Floor:
                sprite.setTexture(mTextures.get(textures.floor));
                break;
            case TileType::Wall:
                sprite.setTexture(mTextures.get(textures.wall));
                break;
            case TileType::DestructibleWall:
                sprite.setTexture(mTextures.get(textures.destructibleWall));
                break;
            }

            if (mMap[y][x].trapType != TrapType::None)
            {
                sf::Sprite trapSprite;
                trapSprite.setPosition(x * mTileSize.x, y * mTileSize.y);
                trapSprite.setTexture(mTextures.get(textures.trap));
                mSprites.push_back(trapSprite);
            }

            mSprites.push_back(sprite);
        }
    }
}

void TileMap::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    for (const auto& sprite : mSprites)
    {
        target.draw(sprite, states);
    }
}

void TileMap::updateCurrent(sf::Time dt, CommandQueue& commands)
{
}

void TileMap::setTile(int x, int y, TileType type)
{
    if (x >= 0 && x < mMap[0].size() && y >= 0 && y < mMap.size())
    {
        mMap[y][x].type = type;
    }
}

void TileMap::spawnPortal()
{
    mPortal = std::make_unique<Portal>(mTextures.get(Textures::Portal));

    std::vector<sf::Vector2i> floorTiles;
    for (int y = 0; y < mMap.size(); ++y)
    {
        for (int x = 0; x < mMap[y].size(); ++x)
        {
            if (mMap[y][x].type == TileType::Floor && mMap[y][x].trapType == TrapType::None)
            {
                floorTiles.push_back({ x, y });
            }
        }
    }

    if (!floorTiles.empty())
    {
        std::uniform_int_distribution<> dis(0, floorTiles.size() - 1);
        sf::Vector2i pos = floorTiles[dis(mRandom)];
        mPortal->setPosition(pos.x * mTileSize.x, pos.y * mTileSize.y);
        attachChild(std::move(mPortal));
    }
}

void TileMap::clearPortal()
{
    if (mPortal)
    {
        detachChild(*mPortal);
        mPortal = nullptr;
    }
    mPlayerEnteredPortal = false; 
}

bool TileMap::hasPlayerEnteredPortal() const
{
    return mPlayerEnteredPortal;
}

void TileMap::resetPlayerEnteredPortal()
{
    mPlayerEnteredPortal = false;
}

void TileMap::playerEnteredPortal()
{
    mPlayerEnteredPortal = true;
}

unsigned int TileMap::getCategory() const
{
    return Category::TileMap;
}
