#ifndef THUNDER_ENGINE
#define THUNDER_ENGINE

#include "HPP/olcPixelGameEngine.h"
#include "HPP/Shapes.hpp"
#include "HPP/Vector.hpp"
#include "Player.hpp"
#include "Tile.hpp"

enum class state {PLAYING, PAUSED, GAMEOVER, NEXTLEVEL};

class Thunder : public olc::PixelGameEngine
{
public:
	Thunder()
	{
		sAppName = "Thunder Platformer";
	}

public:

    Clock m_AnimTimer;

    state m_GameState;

    Player m_Player;

    Tile** m_TileMap = nullptr;
    VectorI m_LevelSize;
    
    int m_CurrentLevel = 0;
    int m_MAX_Level = 2;
    int m_CurrentWorld = 1;
    int m_MAX_World = 1;
    VectorI m_StartingPoint;
    RectF m_GoalPosition;

    RectF m_Camera = RectF({0,0},{320,180});

    Tile** LevelManager(int _Level = 0, int _World = 0);
    void NextLevel();

public:
	bool OnUserCreate() override
	{
        m_GameState = state::GAMEOVER;

        NextLevel();

        m_Player.spawn(m_StartingPoint);

        m_Player.Setup();
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
        // 0-------------------0
        // |    Input/Sound    |
        // 0-------------------0

        if (GetKey(olc::ESCAPE).bPressed) // Close window if esc is pressed
        {
            return false;
        }

        if (GetKey(olc::Key::ENTER).bPressed) // If Enter is pressed
		{
            if (m_GameState != state::NEXTLEVEL) //Dont allow the game to run during level loading
            {
                if (m_GameState != state::PLAYING )
                {
                    m_GameState = state::PLAYING;
                }
                else
                {
                    m_GameState = state::PAUSED;
                }
            }
		}
        if (m_GameState == state::PLAYING) // Playing
        {

            if (m_Player.handleInput(this)) //C heck for input from player
            {
                // Play a jump sound
            }
        }

        // #####################

        // 0-------------------0
        // | Update            |
        // 0-------------------0

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
            m_TileMap[y][x].pos += m_TileMap[y][x].vel * GetElapsedTime();

            m_Player.update(GetElapsedTime());

            m_Player.fall();

            for (int y = 0; y < m_LevelSize.y; y++)
            for (int x = 0; x < m_LevelSize.x; x++)
            if (m_TileMap[y][x].getType() != TileTypes::AIR && 
                m_Player.detectCollision(m_TileMap[y][x], GetElapsedTime()))
            {
                if (m_TileMap[y][x].getType() != TileTypes::GOAL)
                m_Player.resolveCollision(m_TileMap[y][x]);
                else
                {
                    m_GameState == state::NEXTLEVEL;
                    NextLevel();
                }
                
            }

            m_Camera.pos.x = m_Player.pos.x - 148;
            m_Camera.pos.y = m_Player.pos.y - 100;
        }

        

        // #####################

        // 0-------------------0
        // | Animate           |
        // 0-------------------0

        if (m_AnimTimer.GetElapsedTime() > 0.048f)
        {
            if (m_GameState == state::GAMEOVER) // GameOver
            {

            }
            if (m_GameState == state::PAUSED) // Paused
            {

            }
            if (m_GameState == state::PLAYING) // Playing
            {
                m_AnimTimer.Restart();
                m_Player.animate();
            }
            
        }

        // #####################

		// 0-------------------0
        // | Draw              |
        // 0-------------------0
        Clear(olc::Pixel(34,128,218));

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
            {
                if (m_TileMap[y][x].getType() != TileTypes::AIR && m_TileMap[y][x].getType() != TileTypes::GOAL)
                m_TileMap[y][x].drawSelf(this, m_Camera.pos);
            }

            m_Player.drawSelf(this, m_Camera.pos);
        }

        // #####################
			
		return true;
	}

    bool OnUserDestroy() override
    {
        for (int y = 0; y < 11; y++)
        delete[] m_TileMap[y];
        delete[] m_TileMap;
        
        return true;
    }
};

#endif