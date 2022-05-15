#include "someTools.h"

int someTools::RenderCopyExByCenter(SDL_Renderer* renderer, SDL_Texture* texture, const SDL_Rect* srcrect, const SDL_Rect* dstrect, const double angle, const SDL_Point* center, const SDL_RendererFlip flip)
{
	SDL_Rect trueDst = *dstrect;
	trueDst.x = dstrect->x - (dstrect->w >> 1);
	trueDst.y = dstrect->y - (dstrect->h >> 1);
	return SDL_RenderCopyEx(renderer, texture, srcrect, &trueDst, angle, center, flip);
}

std::vector<int> someTools::readNumFromStr(std::string& str)
{
	std::vector<int>val{};
	int sum = 0, flag = 1;
	bool read = false;
	for (const char& q : str)
	{
		if (q >= '0' && q <= '9')
		{
			sum *= 10;
			sum += q - '0';
			read = true;
		}
		else if (q == '-' && !read)
		{
			flag = -1;
		}
		else if (read)
		{
			val.push_back(sum * flag);
			sum = 0;
			read = false;
			flag = 1;
		}
	}
	if (read && sum)val.push_back(sum * flag);
	return val;
}