#include "SDL2/SDL.h"
#include <iostream>
int main(int argc, char* argv[])
{
	if (SDL_Init(SDL_INIT_VIDEO) > 0)
		printf("SDL_INIT_VIDEO ERROR : %s\n", SDL_GetError());
	auto mainWindow = SDL_CreateWindow("我超啊", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, 0);
	bool running = true;
	SDL_Event event;
	while (running)
	{
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				running = false;
				break;
			}
		}
	}
	SDL_DestroyWindow(mainWindow);
	SDL_Quit();
	return 0;
}