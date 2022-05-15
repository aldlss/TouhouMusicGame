#include "SDL2/SDL.h"
#include <iostream>
#include "theGame.h"
int main(int argc, char* argv[])
{
	theGame game;
	if (game.Initialize())
		game.Loop();
	game.Shutdown();
	return 0;
}