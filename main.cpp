#define OLC_PGE_APPLICATION
#include "Thunder.hpp"

int main()
{
	Thunder game;
	if (game.Construct(320, 180, 3, 3))
		game.Start();

	return 0;
}
