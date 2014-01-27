#include "Game.h"

int main()
{
	Game *g = new Game();

	g->run();

	g->~Game();
    return 0;
}