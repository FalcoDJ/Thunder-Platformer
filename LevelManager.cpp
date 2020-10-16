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

	//Prepare a 2d array to hold the type of each tile
	std::string typeOfTile[m_LevelSize.y];
	//Record each type of tile in the array
	int y = 0;
	while (inputFile >> typeOfTile[y])
	{
		y++;
	}

	//Setup some tile stuff
	for (int y = 0; y < m_LevelSize.y; y++)
	{
		for (int x = 0; x < typeOfTile[y].length(); x++) {

			const char type = typeOfTile[y][x];

			if (type == '!')
			{
				_LevelArray[y][x].setTileType('*');
				typeOfTile[y][x] = '*';
				m_StartingPoint.x = x * 16;
				m_StartingPoint.y = y * 16;
			}
			else
			{
				int tileFrame = 1;

				if (type == 'G')
				{
					tileFrame = 10;

					if (y < m_LevelSize.y - 1)
						{
							if (typeOfTile[y - 1][x] == 'G'
							&&  typeOfTile[y + 1][x] == 'G'
							&&  typeOfTile[y][x - 1] == 'G'
							&&  typeOfTile[y][x + 1] == 'G')
							{
								//Surrounded by ground
								tileFrame = 10;
							}
							else if (typeOfTile[y - 1][x] == 'G'
								 &&  typeOfTile[y + 1][x] == 'G'
								 &&  typeOfTile[y][x - 1] == 'G'
								 &&  typeOfTile[y][x + 1] != 'G')
							{
								//Surrounded by three (none on right)
								tileFrame = 11;
							}
							else if (typeOfTile[y - 1][x] == 'G'
								 &&  typeOfTile[y + 1][x] == 'G'
								 &&  typeOfTile[y][x + 1] == 'G'
								 &&  typeOfTile[y][x - 1] != 'G')
							{
								//Surrounded by three (none on left)
								tileFrame = 9;
							}
							else if (typeOfTile[y - 1][x] == 'G'
								 &&  typeOfTile[y + 1][x] != 'G'
								 &&  typeOfTile[y][x - 1] == 'G'
								 &&  typeOfTile[y][x + 1] == 'G')
							{
								//Surrounded by three (none on bottom)
								tileFrame = 14;
							}
							else if (typeOfTile[y + 1][x] == 'G'
								 &&  typeOfTile[y - 1][x] != 'G'
								 &&  typeOfTile[y][x - 1] == 'G'
								 &&  typeOfTile[y][x + 1] == 'G')
							{
								//Surrounded by three (none on top)
								tileFrame = 6;
							}
							else if (typeOfTile[y - 1][x] == 'G'
								 &&  typeOfTile[y][x - 1] == 'G'
								 &&  typeOfTile[y + 1][x] != 'G'
								 &&  typeOfTile[y][x + 1] != 'G')
							{
								//touched on top & right
								tileFrame = 15;
							}
							else if (typeOfTile[y - 1][x] == 'G'
								 &&  typeOfTile[y][x - 1] != 'G'
								 &&  typeOfTile[y + 1][x] != 'G'
								 &&  typeOfTile[y][x + 1] == 'G')
							{
								//touched on top & left
								tileFrame = 13;
							}
							else if (typeOfTile[y - 1][x] != 'G'
								 &&  typeOfTile[y][x - 1] != 'G'
								 &&  typeOfTile[y + 1][x] == 'G'
								 &&  typeOfTile[y][x + 1] == 'G')
							{
								//touched on bottom & right
								tileFrame = 5;
							}
							else if (typeOfTile[y - 1][x] != 'G'
								 &&  typeOfTile[y][x - 1] == 'G'
								 &&  typeOfTile[y + 1][x] == 'G'
								 &&  typeOfTile[y][x + 1] != 'G')
							{
								//touched on bottom & left
								tileFrame = 7;
							}
							else if (typeOfTile[y - 1][x] != 'G'
								 &&  typeOfTile[y][x - 1] == 'G'
								 &&  typeOfTile[y + 1][x] != 'G'
								 &&  typeOfTile[y][x + 1] == 'G')
							{
								//touched x axis
								tileFrame = 2;
							}
							else if (typeOfTile[y - 1][x] == 'G'
								 &&  typeOfTile[y][x - 1] != 'G'
								 &&  typeOfTile[y + 1][x] == 'G'
								 &&  typeOfTile[y][x + 1] != 'G')
							{
								//touched y axis
								tileFrame = 12;
							}
							else if (typeOfTile[y - 1][x] == 'G'
								 &&  typeOfTile[y][x - 1] != 'G'
								 &&  typeOfTile[y + 1][x] != 'G'
								 &&  typeOfTile[y][x + 1] != 'G')
							{
								//touched y axis
								tileFrame = 16;
							}
							else if (typeOfTile[y - 1][x] != 'G'
								 &&  typeOfTile[y][x - 1] != 'G'
								 &&  typeOfTile[y + 1][x] == 'G'
								 &&  typeOfTile[y][x + 1] != 'G')
							{
								//touched y axis
								tileFrame = 8;
							}
							else if (typeOfTile[y - 1][x] != 'G'
								 &&  typeOfTile[y][x - 1] != 'G'
								 &&  typeOfTile[y + 1][x] != 'G'
								 &&  typeOfTile[y][x + 1] == 'G')
							{
								//touched y axis
								tileFrame = 1;
							}
							else if (typeOfTile[y - 1][x] != 'G'
								 &&  typeOfTile[y][x - 1] == 'G'
								 &&  typeOfTile[y + 1][x] != 'G'
								 &&  typeOfTile[y][x + 1] != 'G')
							{
								//touched y axis
								tileFrame = 3;
							}
						}
				}
				
				_LevelArray[y][x].setTileType(type, tileFrame);
			}
			
			_LevelArray[y][x].pos.x = x * 16;
			_LevelArray[y][x].pos.y = y * 16;
		}
	}

	// close the file
	inputFile.close();

	return _LevelArray;

}