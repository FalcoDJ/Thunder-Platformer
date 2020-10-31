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
            
        }
    }
    if (m_GameState == state::PLAYING) // Playing
    {

        if (m_Player.handleInput(this)) //C heck for input from player
        {
            // Play a jump sound
        }
    }
}