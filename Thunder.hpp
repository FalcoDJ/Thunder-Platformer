#ifndef THUNDER_ENGINE
#define THUNDER_ENGINE

#include "HPP/olcPixelGameEngine.h"
#include "HPP/Vector.hpp"
#include "HPP/Shapes.hpp"
#include "HPP/Collision.hpp"
#include "Player.hpp"
#include "Tile.hpp"


enum class state {PLAYING, PAUSED, GAMEOVER, NEXTLEVEL};

class Thunder : public olc::PixelGameEngine
{
public:
    VectorI m_ScreenSize = {320,180};

	Thunder()
	{
		sAppName = "Thunder Platformer";
	}

private:
    void handleInput();
    void update();
    void draw();

private:
    int m_LayerUI = 1; //User interface layer
    int m_LayerMG = 2; //Main Game layer
    int m_LayerBG = 3; //Background layer

private:

    Clock m_AnimTimer;

    state m_GameState;

    olc::Decal* m_Background = nullptr;

    Player m_Player;

    Tile** m_TileMap = nullptr;
    VectorI m_LevelSize;
    
    int m_CurrentLevel = 0;
    int m_MAX_Level = 3;
    int m_CurrentWorld = 1;
    int m_MAX_World = 1;
    VectorI m_StartingPoint;
    RectF m_GoalPosition;

    RectF m_Camera = RectF({0,0},{320,180});
    int m_MAX_ShakeMag = 4;
    bool m_ScreenShake;

    void NewBG(std::string _path2S = "assets/GameOver.png");
    Tile** LevelManager(int _Level = 0, int _World = 0);
    void NextLevel(state _Gst = state::PAUSED);

public:
	bool OnUserCreate() override
	{
        m_LayerUI = CreateLayer();
        EnableLayer(m_LayerUI, true);
        SetDrawTarget(m_LayerUI);
        SetPixelMode(olc::Pixel::ALPHA);
        Clear(olc::BLANK);

        m_LayerMG = CreateLayer();
        EnableLayer(m_LayerMG, true);
        SetDrawTarget(m_LayerMG);
        SetPixelMode(olc::Pixel::ALPHA);
        Clear(olc::BLANK);

        m_LayerBG = CreateLayer();
        EnableLayer(m_LayerBG, true);
        SetDrawTarget(m_LayerBG);
        SetPixelMode(olc::Pixel::ALPHA);
        Clear(olc::BLANK);

        SetDrawTarget(nullptr);
        SetPixelMode(olc::Pixel::ALPHA);
        Clear(olc::BLANK);

        SetDrawTarget(m_LayerUI);

        m_GameState = state::GAMEOVER;
        
        m_Player.spawn(m_StartingPoint);

        m_Player.Setup();

        NewBG();
        
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
                if (m_GameState == state::GAMEOVER)
                {

                    m_CurrentLevel = 0;
                    m_CurrentWorld = 1;

                    m_Player.reset();

                    //Restart the Game
                    NextLevel(state::PLAYING);
                }
                else if (m_GameState != state::PLAYING)
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

            std::cout << "Player X: " << m_Player.center().x << " Player Y: " << m_Player.center().y << std::endl;

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
                    else if (m_TileMap[y][x].getType() == TileTypes::LAVA 
                    ||       m_TileMap[y][x].getType() == TileTypes::SPIKE)
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

            m_Camera.pos.x = m_Player.pos.x - 148;
            m_Camera.pos.y = m_Player.pos.y - 100;
            
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

            //If player goes outside of camera end him ( Game Over :( !)
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

        // #####################
			
		return true;
	}

    bool OnUserDestroy() override
    {
        for (int y = 0; y < m_LevelSize.y; y++)
        delete[] m_TileMap[y];
        delete[] m_TileMap;
        
        return true;
    }
};

#endif