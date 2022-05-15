#include "theGame.h"
#include <iostream>
#include "Levers.h"
theGame::theGame()
	:isRunning(true), renderer(nullptr), window(nullptr), fileReader()
{

}

bool theGame::Initialize()
{
	if (SDL_Init(SDL_INIT_EVERYTHING))
	{
		printf("fail to SDL_Init SDL_INIT_EVERYTHING : %s\n", SDL_GetError());
		return false;
	}
	if (!IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG))
	{
		printf("fail to IMG_Init : %s\n", SDL_GetError());
		return false;
	}
	if (!Mix_Init(MIX_INIT_MP3 | MIX_INIT_FLAC))
	{
		printf("fail to MIX_Init : %s\n", SDL_GetError());
		return false;
	}
	if (TTF_Init())
	{
		printf("fail to TTF_Init : %s\n", SDL_GetError());
		return false;
	}
	window = SDL_CreateWindow("Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, 0);
	if (window == nullptr)
	{
		printf("fail to CreateWindow : %s\n", SDL_GetError());
		return false;
	}
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == nullptr)
	{
		printf("fail to CreateRenderer : %s\n", SDL_GetError());
		return false;
	}
	return true;
}

void theGame::Loop()
{
	levers toLever = PristineBeat;
	fileReader.open(R"(F:\code\work\TouhouMusicGame\resources\musicNotationFile\PristineBeat.txt)", std::ios::in);
	roundLevel* lever = new roundLevel(renderer, window, fileReader);
	toLever = lever->running();
	while (isRunning)
	{
		switch (toLever)
		{
		case Quit:
			isRunning = false;
			delete lever;
			break;
		case PristineBeat:
			delete lever;
		}
	}
	fileReader.close();
}

void theGame::Shutdown()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	IMG_Quit();
	TTF_Quit();
	Mix_Quit();
}