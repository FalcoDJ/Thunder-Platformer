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
                    
                    //Play a sound for coins
                    olc::SOUND::PlaySample(sCoin);
                }
                
                if (m_TileMap[y][x].getType() == TileTypes::LAVA)
                {
                    m_Player.stopFalling(m_TileMap[y][x].pos.y);

                    if (m_Player.getState() != Creature::state::INVINSIBLE)
                    {
                        ShakeScreen();
                        if (m_Player.dye()) //If player is out of lives
                        {
                            m_GameState = state::GAMEOVER;
                        }
                        m_Player.vel.y = -900;
                        
                        //Play a hurt sound
                        olc::SOUND::PlaySample(sHurt);
                    }
                }
                if (m_TileMap[y][x].getType() == TileTypes::SPIKE)
                {
                    if (m_Player.getState() != Creature::state::INVINSIBLE)
                    {
                        ShakeScreen();
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

        //Camera follows player

        m_Camera.pos.x = Math::lerp(m_Camera.center().x, m_Player.center().x, 0.17f) - m_Camera.size.x/2;
        m_Camera.pos.y = Math::lerp(m_Camera.center().y, m_Player.center().y, 0.17f) - m_Camera.size.y/2;
        
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

        //Screen Shake

        if (m_ScreenShake)
        {
            if ((rand() % 1) > .5)
            {
                m_Camera.pos.x = Math::lerp(m_Camera.center().x + rand() % m_MAX_ShakeMag, m_Player.center().x, 0.003f) - m_Camera.size.x/2;
                m_Camera.pos.y = Math::lerp(m_Camera.center().y - rand() % m_MAX_ShakeMag, m_Player.center().y, 0.003f) - m_Camera.size.y/2;
            }
            else
            {
                m_Camera.pos.x = Math::lerp(m_Camera.center().x - rand() % m_MAX_ShakeMag, m_Player.center().x, 0.003f) - m_Camera.size.x/2;
                m_Camera.pos.y = Math::lerp(m_Camera.center().y + rand() % m_MAX_ShakeMag, m_Player.center().y, 0.003f) - m_Camera.size.y/2;
            }
            if (m_ShakeTimer.GetElapsedTime() > 0.032)
            {
                m_ScreenShake = false;
            }
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