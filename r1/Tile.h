#pragma once

enum class TileType
{
    Floor,
    Wall,
    DestructibleWall
};

enum class TrapType
{
    None,
    Spikes,
    Mine
};

struct Tile
{
    Tile();
    TileType type;
    TrapType trapType;
};