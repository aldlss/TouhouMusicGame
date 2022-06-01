#pragma once
#include "imgui/backends/imgui_impl_sdl.h"
#include "imgui/backends/imgui_impl_sdlrenderer.h"
#include "theGame.h"
#include "SDL2/SDL.h"
class startUI
{
protected:
	SDL_Renderer* renderer;
public:
	startUI(SDL_Renderer* renderer);
	theGame::levers run();
};

