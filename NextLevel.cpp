#include "Thunder.hpp"

void Thunder::NextLevel(state _Gst)
{
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
    std::cout << "Player X: " << m_Player.center().x << " Player Y: " << m_Player.center().y << std::endl;

    m_GameState = _Gst;
}