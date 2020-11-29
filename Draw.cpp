#include "Thunder.hpp"

void Thunder::draw()
{
    SetDrawTarget(m_LayerUI);
    SetPixelMode(olc::Pixel::ALPHA);
    Clear(olc::BLANK);
    SetPixelMode(olc::Pixel::NORMAL);

    if (m_GameState != state::PAUSED)
    {
    SetDrawTarget(m_LayerMG);
    SetPixelMode(olc::Pixel::ALPHA);
    Clear(olc::BLANK);
    SetPixelMode(olc::Pixel::NORMAL);
    }

    SetDrawTarget(m_LayerBG);
    SetPixelMode(olc::Pixel::ALPHA);
    Clear(m_BGcolor);
    SetPixelMode(olc::Pixel::NORMAL);

    if (m_GameState == state::GAMEOVER) // GameOver
    {
        // 0-----------------0
        // | Draw Background |
        // 0-----------------0

        SetDrawTarget(m_LayerBG);
        Clear(olc::BLACK);
        DrawDecal({(m_ScreenSize.x - m_GameOverSize.x)/2, (m_ScreenSize.y - m_GameOverSize.y)/2}, m_Background);
    }
    else
    {
        // 0-----------------0
        // | Draw Background |
        // 0-----------------0
        
        SetDrawTarget(m_LayerBG);
        //Make background move slightly with camera
        DrawDecal({m_Camera.pos.x * -.05, 0}, m_Background);


        // 0----------------0
        // | Draw MG Layer  |
        // 0----------------0

        SetDrawTarget(m_LayerMG);

        for (int y = 0; y < m_LevelSize.y; y++)
        for (int x = 0; x < m_LevelSize.x; x++)
        {
            if (detectCollision(m_Camera, m_TileMap[y][x]))
            if (m_TileMap[y][x].getType() != TileTypes::AIR && m_TileMap[y][x].getType() != TileTypes::GOAL)
            m_TileMap[y][x].drawSelf(this, m_Camera.pos);
        }

        m_Player.drawSelf(this, m_Camera.pos);

        // 0----------------0
        // | Draw Ui Layer  |
        // 0----------------0

        SetDrawTarget(m_LayerUI);

        if (m_GameState == state::PAUSED)
        {
            if (StartedNewLevel)
            Clear(olc::BLANK);
            else
            {
                Clear(olc::BLACK);
            }
            
            FillRect({(m_ScreenSize.x - m_PausedSize.x)/2 - 4, (m_ScreenSize.y - m_PausedSize.y)/2 - 4}, {72, 48}, olc::BLACK);
            DrawDecal({(m_ScreenSize.x - m_PausedSize.x)/2, (m_ScreenSize.y - m_PausedSize.y)/2}, m_PausedIMG);
            //Health Bar
            FillRect({m_ScreenSize.x/2 - 32, m_ScreenSize.y/2 + 20}, {(m_Player.getLives()/5)*64, 4}, olc::GREEN);
            FillRect({(m_Player.getLives()/5)*64 + m_ScreenSize.x/2 - 32,m_ScreenSize.y/2 + 20}, {64 - (m_Player.getLives()/5)*64,4}, olc::RED);
        }
        else
        {   
            //Health Bar
            FillRect({8,8}, {(m_Player.getLives()/5)*80, 8}, olc::GREEN);
            FillRect({(m_Player.getLives()/5)*80 + 8,8}, {80 - (m_Player.getLives()/5)*80,8}, olc::RED);
            DrawRect({7,7}, {80,8}, olc::BLACK);
        }
    }
}