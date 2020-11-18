#include "Thunder.hpp"

void Thunder::update()
{
    if (m_GameState == state::NEXTLEVEL) // NextLevel
    {
        NextLevel();
    }
    if (m_GameState == state::GAMEOVER) // GameOver
    {

    }
    if (m_GameState == state::PAUSED) // Paused
    {

    }

    if (m_GameState == state::PLAYING) //Playing
    {
        for (int y = 0; y < m_LevelSize.y; y++)
        for (int x = 0; x < m_LevelSize.x; x++)
        m_TileMap[y][x].update(GetElapsedTime());

        m_Player.update(GetElapsedTime());

        m_Player.fall();

        for (int y = 0; y < m_LevelSize.y; y++)
        for (int x = 0; x < m_LevelSize.x; x++)
        if (m_TileMap[y][x].getType() != TileTypes::AIR && 
            m_Player.detectCollision(m_TileMap[y][x], GetElapsedTime()))
        {
            if (m_TileMap[y][x].getType() == TileTypes::GOAL)
            m_GameState = state::NEXTLEVEL;
            else
            {
                if (m_TileMap[y][x].getType() == TileTypes::GROUND)
                {
                    m_Player.resolveCollision(m_TileMap[y][x]);
                }
                else if (m_TileMap[y][x].getType() == TileTypes::COIN)
                {
                    m_TileMap[y][x].setTileType('*');
                }
                else if (m_TileMap[y][x].getType() == TileTypes::LAVA)
                {
                    if (m_Player.getState() != Creature::state::INVINSIBLE)
                    {
                        m_ScreenShake = true;
                        m_Player.stopFalling(m_TileMap[y][x].pos.y);
                        if (m_Player.dye()) //If player is out of lives
                        {
                            m_GameState = state::GAMEOVER;
                        }
                        m_Player.vel.y = -900;
                    }
                }
                else if (m_TileMap[y][x].getType() == TileTypes::SPIKE)
                {
                    if (m_Player.getState() != Creature::state::INVINSIBLE)
                    {
                        m_ScreenShake = true;
                        m_Player.stopFalling(m_TileMap[y][x].pos.y);
                        if (m_Player.dye()) //If player is out of lives
                        {
                            m_GameState = state::GAMEOVER;
                        }
                        m_Player.vel.y = -900;
                    }
                }
            }
            
        }

        m_Camera.center(m_Player.pos);
        
        //Camera Cant Go Past screen edges
        
        // X
        if (m_Camera.pos.x < 0)
        {
            m_Camera.pos.x = 0;
        }
        if (m_Camera.right() > m_LevelSize.x * 16)
        {
            m_Camera.pos.x = m_LevelSize.x * 16 - m_Camera.size.x;
        }

        // Y 
        if (m_Camera.bottom() > m_LevelSize.y * 16)
        {
            m_Camera.pos.y = m_LevelSize.y * 16 - m_Camera.size.y;
        }

        if (m_ScreenShake)
        {
            if ((rand() & 1) > .5)
            {
                m_Camera.pos.x += rand() % m_MAX_ShakeMag;
                m_Camera.pos.y -= rand() % m_MAX_ShakeMag;
            }
            else
            {
                m_Camera.pos.x -= rand() % m_MAX_ShakeMag;
                m_Camera.pos.y += rand() % m_MAX_ShakeMag;
            }
            m_ScreenShake = false;
        }

        // ! Put camera boundaries here !

        //If player goes outside of camera end him! [ Game Over :( ]
        if (!m_Player.detectCollision(m_Camera, GetElapsedTime()))
        {
            m_GameState = state::GAMEOVER;
        }

        //If game has entered into GameOver mode this frame
        if (m_GameState == state::GAMEOVER)
        {
            NewBG();
        }
    }
}