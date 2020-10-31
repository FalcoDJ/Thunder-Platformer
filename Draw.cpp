#include "Thunder.hpp"

void Thunder::draw()
{
    SetDrawTarget(m_LayerUI);
    Clear(olc::BLANK);

    SetDrawTarget(m_LayerMG);
    Clear(olc::BLANK);

    SetDrawTarget(m_LayerBG);
    Clear(olc::Pixel(34,128,218));

    if (m_GameState == state::GAMEOVER) // GameOver
    {
        SetDrawTarget(m_LayerBG);
        Clear(olc::BLACK);
        DrawDecal({128, 66}, m_Background);
    }
    else
    {
        SetDrawTarget(m_LayerBG);
        //Make background move slightly with camera
        DrawDecal({m_Camera.pos.x * -.05, 0}, m_Background);

        SetDrawTarget(m_LayerMG);

        for (int y = 0; y < m_LevelSize.y; y++)
        for (int x = 0; x < m_LevelSize.x; x++)
        {
            if (detectCollision(m_Camera, m_TileMap[y][x]))
            if (m_TileMap[y][x].getType() != TileTypes::AIR && m_TileMap[y][x].getType() != TileTypes::GOAL)
            m_TileMap[y][x].drawSelf(this, m_Camera.pos);
        }

        m_Player.drawSelf(this, m_Camera.pos);

        if (m_GameState == state::PAUSED)
        {
            SetDrawTarget(m_LayerUI);
            FillRect(0, 0, m_ScreenSize.x, m_ScreenSize.y, olc::Pixel(28,28,28));
        }
    }
}