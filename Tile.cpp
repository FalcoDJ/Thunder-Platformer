#include "Tile.hpp"
#include "HPP/FrameGrabber.hpp"

void Tile::drawSelf(olc::PixelGameEngine *pge, VectorF Camera)
{
    DrawDecalFrame(pge, m_Decal, pos, m_SpriteData, m_FramesPer, m_CurFrame, Camera);
}

void Tile::Setup()
{
    m_Sprite = new olc::Sprite(pathToSprite);
    m_Decal = new olc::Decal(m_Sprite);
}

void Tile::setTileType(char _type, int _frame)
{
    m_CurFrame = _frame;

    /***/if (_type == '#')
    {
        m_MyType = TileTypes::GOAL;
    }
    else if (_type == '*')
    {
        m_MyType = TileTypes::AIR;
    }
    else if (_type == '@') // @ = COIN
    {
        m_MyType = TileTypes::COIN;
        m_CurFrame = 24;
    }
    else if (_type == 'G') // G = GROUND
    {
        m_MyType = TileTypes::GROUND;
    }
    else if (_type == 'W') // W = WATER
    {
        m_MyType = TileTypes::WATER;
    }
    else if (_type == 'I') // I = ICE
    {
        m_MyType = TileTypes::ICE;
    }
    else if (_type == 'L') // L = LAVA
    {
        m_MyType = TileTypes::LAVA;
        m_CurFrame = 22;
    }
    else if (_type == 'V')
    {
        m_MyType == TileTypes::SPIKE;
        m_CurFrame = 18;
    }
    m_CurFrame -= 1;
}