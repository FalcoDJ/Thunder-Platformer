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

            handleInput();

        // #####################

        // 0-------------------0
        // | Update            |
        // 0-------------------0
        
            update();

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
        
            draw();

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