#define OLC_PGE_APPLICATION
#define OLC_PGEX_SOUND

#ifdef __linux__
#undef USE_ALSA
#define USE_OPENAL
#endif

#include "Thunder.hpp"

int main()
{
	Thunder game;
	if (game.Construct(game.m_ScreenSize.x, game.m_ScreenSize.y, 3, 3))
		game.Start();

	return 0;
}
