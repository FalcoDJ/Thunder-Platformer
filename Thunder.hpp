#ifndef THUNDER_ENGINE
#define THUNDER_ENGINE

//Include game engine heade file
#include "HPP/olcPixelGameEngine.h"

//Audio header file(s)
#include "HPP/olcPGEX_Sound.h"

//Include my header files
#include "HPP/Math.hpp"
#include "HPP/Shapes.hpp"
#include "HPP/Collision.hpp"
#include "Player.hpp"
#include "Tile.hpp"

enum class state {PLAYING, PAUSED, GAMEOVER, NEXTLEVEL};

class Thunder : public olc::PixelGameEngine
{
public:
    VectorI m_ScreenSize = {384,216};

	Thunder()
	{
		sAppName = "Thunder Platformer";
	}

private:
    void handleInput();
    void update();
    void draw();

private: //Layer Stuff
    int m_LayerUI = 1; //User interface layer
    int m_LayerMG = 2; //Main Game layer
    int m_LayerBG = 3; //Background layer

    olc::Pixel m_BGcolor;

    bool StartedNewLevel;

private: //Sound stuff
    static float fVolume;

    int sJump;
    int sHurt;
    int sCoin;

	static float AdjustVolume(int nChannel, float fGlobalTime, float fSample)
	{
		// Fundamentally just control volume
		float fOutput = fSample * fVolume;
        
		return fOutput;
	}
    

private: // other stuff

    Clock m_AnimTimer;

    state m_GameState;

    olc::Decal* m_Background = nullptr;
    VectorF m_GameOverSize = {64,48};

    olc::Decal* m_PausedIMG = nullptr;
    VectorF m_PausedSize = {64,32};

    olc::Decal* m_LevelDecal = nullptr;

    Player m_Player;

    Tile** m_TileMap = nullptr;
    VectorI m_LevelSize;
    
    int m_CurrentLevel = 0;
    int m_MAX_Level = 3;
    int m_CurrentWorld = 1;
    int m_MAX_World = 1;
    VectorI m_StartingPoint;
    RectF m_GoalPosition;

    RectF m_Camera = RectF({0,0},m_ScreenSize);

    Clock m_ShakeTimer;
    int m_MAX_ShakeMag = 6;
    bool m_ScreenShake;
    void ShakeScreen() { m_ShakeTimer.Restart(); m_ScreenShake = true; }

    void NewBG(std::string _path2S = "assets/GameOver.png");
    Tile** LevelManager(int _Level = 0, int _World = 0);
    void NextLevel(state _Gst = state::PAUSED);

public:
	bool OnUserCreate() override
	{
        //
        //Initialize sound/audio
        //
        olc::SOUND::InitialiseAudio();
        olc::SOUND::SetUserFilterFunction(AdjustVolume);

        sJump = olc::SOUND::LoadAudioSample("assets/gen_SFX/Jump.wav");
        sHurt = olc::SOUND::LoadAudioSample("assets/gen_SFX/Hurt.wav");
        sCoin = olc::SOUND::LoadAudioSample("assets/gen_SFX/Pickup_Coin.wav");

        //
        //Initialize other stuff
        //

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

        SetDrawTarget(nullptr);

        olc::Sprite* tempSprite = new olc::Sprite("assets/Paused.png");

        m_PausedIMG = new olc::Decal(tempSprite);

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

        if (m_AnimTimer.GetElapsedTime() > 0.08f)
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
        olc::SOUND::DestroyAudio();

        for (int y = 0; y < m_LevelSize.y; y++)
        delete[] m_TileMap[y];
        delete[] m_TileMap;
        
        return true;
    }
};

#endif