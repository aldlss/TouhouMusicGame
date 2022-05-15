#pragma once
#include "SDL2/SDL.h"
#include "vector"
#include "string"
class someTools
{
public:
	//以给予的坐标为中心画图
	static int RenderCopyExByCenter(SDL_Renderer* renderer,
		SDL_Texture* texture,
		const SDL_Rect* srcrect,
		const SDL_Rect* dstrect,
		const double angle,
		const SDL_Point* center,
		const SDL_RendererFlip flip);
	static std::vector<int>	readNumFromStr(std::string& str);
};

