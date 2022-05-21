#pragma once
#include <string>
#include "spriteComponent.h"
#include "SDL2/SDL_ttf.h"
class fontComponent :
	public spriteComponent
{
protected:
	TTF_Font* font;
	std::string str;
	SDL_Color color;
public:
	fontComponent(baseGameObject* ownerInput, TTF_Font* font, SDL_Texture* texture = nullptr, int drawOrder = 120, int priorityInput = 30);
	void setString(const std::string& string);
	void setFont(TTF_Font* fontInput);
	void serColor(const SDL_Color colorInput);
	void draw(SDL_Renderer* renderer) override;//重写是我能想到的最好的实现我的想法的办法了
};

