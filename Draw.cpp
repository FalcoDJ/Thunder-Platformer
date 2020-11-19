#include "Thunder.hpp"

void Thunder::draw()
{
    SetDrawTarget(m_LayerUI);
    Clear(olc::BLANK);

    if (m_GameState != state::PAUSED)
    {
    SetDrawTarget(m_LayerMG);
    Clear(olc::BLANK);
    }

    SetDrawTarget(m_LayerBG);
    Clear(m_BGcolor);

    if (m_GameState == state::GAMEOVER) // GameOver
    {
        // 0-----------------0
        // | Draw Background |
        // 0-----------------0

        SetDrawTarget(m_LayerBG);
        Clear(olc::BLACK);
        DrawDecal({128, 66}, m_Background);
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
            
            FillRect({124, 54}, {72, 48}, olc::BLACK);
            DrawDecal({128, 58}, m_PausedIMG);
            //Health Bar
            FillRect({128,94}, {(m_Player.getLives()/5)*64, 4}, olc::GREEN);
            FillRect({(m_Player.getLives()/5)*64 + 128,94}, {64 - (m_Player.getLives()/5)*64,4}, olc::RED);
        }
        else
        {   
            //Health Bar
            FillRect({8,8}, {(m_Player.getLives()/5)*64, 4}, olc::GREEN);
            FillRect({(m_Player.getLives()/5)*64 + 8,8}, {64 - (m_Player.getLives()/5)*64,4}, olc::RED);
            DrawRect({7,7}, {64,4}, olc::BLACK);
        }
    }
}