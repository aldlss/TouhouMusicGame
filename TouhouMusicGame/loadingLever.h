#pragma once
#include "baseLever.h"
class loadingLever :
	public baseLever
{
public:
	loadingLever(SDL_Renderer* renderer, SDL_Window* window);
	int count;
	void globalEvent() override;
};
