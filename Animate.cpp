#include "Thunder.hpp"

void Thunder::animate()
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