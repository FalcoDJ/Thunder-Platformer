#include "Thunder.hpp"

void Thunder::handleInput()
{
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
            if (!StartedNewLevel)
            {
                StartedNewLevel = true;
            }
        }
    }
    if (m_GameState == state::PLAYING) // Playing
    {

        if (m_Player.handleInput(this)) //Check for input from player
        {
            // Play a jump sound
            olc::SOUND::PlaySample(sJump);
        }
    }

    if (m_GameState == state::PAUSED)
    {
        float fCurVol = fVolume;
        if (GetKey(olc::Key::UP).bPressed)
        {
            fVolume += 0.2f;
        }
        if (GetKey(olc::Key::DOWN).bPressed)
        {
            fVolume -= 0.2f;
        }

        if (fVolume != fCurVol)
        std::cout << "\n New Volume is " << fVolume;
    }
}

float Thunder::fVolume = 1.0f;