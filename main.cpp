#define OLC_PGE_APPLICATION
#define OLC_PGEX_SOUND
#include "Thunder.hpp"

int main()
{
	Thunder game;
	if (game.Construct(game.m_ScreenSize.x, game.m_ScreenSize.y, 3, 3))
		game.Start();

	return 0;
}
