#pragma once
#include "baseLever.h"
#include "queue"
#include "musicalNote.h"
#include "trackObject.h"
class roundLevel :
	public baseLever
{
public:
	roundLevel(SDL_Renderer* renderer, SDL_Window* window, std::ifstream& file, std::string musicRoute, std::string backgroundImgRoute);
protected:
	std::ifstream& musicNotationFile;
	std::vector<std::queue<musicalNote::NodeInfo>>waitingTracks{ 1 };
	std::vector<trackObject*>trackObjects;
	// void globalEvent() override;
};