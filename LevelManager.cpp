#include <sstream>
#include <fstream>
#include "Thunder.hpp"

Tile** Thunder::LevelManager(int _Level, int _World)
{
    m_LevelSize.x = 0;
	m_LevelSize.y = 0;

	// Get the next level
	m_CurrentLevel++;
	if (m_CurrentLevel > m_MAX_Level)
	{
		m_CurrentLevel = 1;
		m_CurrentWorld++;
        if (m_CurrentWorld > m_MAX_World)
        {
            m_CurrentWorld = 1;
        }
	}
	if (_Level > 0 && _World > 0)
	{
		m_CurrentLevel = _Level;
		m_CurrentWorld = _World;
	}

	// Load the appropriate level from a text file
	std::ifstream inputFile("assets/Levels/World" + std::to_string(m_CurrentWorld) + "/" + std::to_string(m_CurrentLevel) + ".txt");
	std::string s;

	// Count the number of rows in the file
	while (getline(inputFile, s))
	{
		++m_LevelSize.y;
	}

	// Store the length of the rows
	m_LevelSize.x = s.length();

	// Go back to the start of the file
	inputFile.clear();
	inputFile.seekg(0, std::ios::beg);

	// Prepare the 2d array to hold the int values from the file
	Tile** _LevelArray = new Tile*[m_LevelSize.y];
	for (int i = 0; i < m_LevelSize.y; ++i)
	{
		// Add a new array into each array element
		_LevelArray[i] = new Tile[m_LevelSize.x];
	}

	// Loop through the file and store all the values in the 2d array
	std::string row;
	int y = 0;
	while (inputFile >> row)
	{
		for (int x = 0; x < row.length(); x++) {

			const char val = row[x];
            _LevelArray[y][x].setTileType(val);
			if (val == '!')
			{
				int tileFrame;
				if (val == 'G')
				{
					//Make auto tile frame selector based on position of tiles around a tile.
				}

				_LevelArray[y][x].setTileType('0', tileFrame);
				m_StartingPoint.x = x * 16;
				m_StartingPoint.y = y * 16;
			}
			_LevelArray[y][x].pos.x = x * 16;
			_LevelArray[y][x].pos.y = y * 16;
		}
		y++;
	}

	// close the file
	inputFile.close();

	return _LevelArray;

}