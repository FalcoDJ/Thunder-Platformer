#include "Thunder.hpp"

void Thunder::NextLevel(state _Gst)
{
    olc::SOUND::StopAll();

    for (int y = 0; y < m_LevelSize.y; y++)
        delete[] m_TileMap[y];
    delete[] m_TileMap;

    // Load next level from text file 
    // using the LevelManager function
    m_TileMap = LevelManager();

    for (int y = 0; y < m_LevelSize.y; y++)
    for (int x = 0; x < m_LevelSize.x; x++)
    m_TileMap[y][x].Setup();

    // ! Spawn Player(s) !
    m_Player.spawn(m_StartingPoint);

    //Put Camera into position (prevents gameover on new level)
    m_Camera.center(m_StartingPoint);

    StartedNewLevel = false;

    m_GameState = _Gst;    

    olc::SOUND::PlaySample(sMusic, true);
}