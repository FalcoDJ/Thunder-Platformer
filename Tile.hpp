#ifndef TILE_HPP
#define TILE_HPP

#include "HPP/Shapes.hpp"
#include "HPP/olcPixelGameEngine.h"

enum class TileTypes {AIR, GROUND, ONE_WAY, WATER, ICE, LAVA, COIN, GOAL};

class Tile : public RectF
{
    public:
    Tile(){size = {16,16};};
    ~Tile(){delete m_Sprite, m_Decal;}

    virtual void update(float ElapsedTime){pos += vel * ElapsedTime;};
    virtual void animate(){};
    void drawSelf(olc::PixelGameEngine *pge, VectorF Camera);

    void Setup();
    virtual void setTileType(char _type, int _frame = 0);
    TileTypes getType(){return m_MyType;};

    protected:
    std::string pathToSprite = "assets/Tiles.png";
    RectF m_SpriteData = RectF({0,0}, {16,16});
    olc::Sprite* m_Sprite = nullptr;
    olc::Decal* m_Decal = nullptr;

    int m_FramesPerRow = 4;
    int m_FramesPerCol = 6;
    int m_MAX_Frames = m_FramesPerRow * m_FramesPerCol;
    int m_CurFrame = 0;

    TileTypes m_MyType;
};

#endif