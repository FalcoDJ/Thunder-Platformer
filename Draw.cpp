#include "Thunder.hpp"

void Thunder::draw()
{
    SetDrawTarget(m_LayerUI);
    Clear(olc::BLANK);

    SetDrawTarget(m_LayerMG);
    Clear(olc::BLANK);

    SetDrawTarget(m_LayerBG);
    Clear(olc::Pixel(0,153,219));

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
            Clear(olc::BLACK);
            DrawDecal({(m_ScreenSize/2).x - 32, (m_ScreenSize/2).y - 16}, m_PausedIMG);
            //Health Bar
            FillRect({112,32}, {(m_Player.getLives()/5)*96, 8}, olc::RED);
            DrawRect({7,7}, {64,4}, olc::BLACK);
        }
        else
        {   
            //Health Bar
            FillRect({8,8}, {(m_Player.getLives()/5)*64, 4}, olc::RED);
            DrawRect({7,7}, {64,4}, olc::BLACK);
        }
    }
}