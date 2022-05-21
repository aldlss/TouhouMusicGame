#include "fontComponent.h"
#include "someTools.h"
#include "baseLever.h"
#include "transformComponent.h"
fontComponent::fontComponent(baseGameObject* ownerInput, TTF_Font* font, SDL_Texture* texture, int drawOrder, int priorityInput)
	:spriteComponent(ownerInput, texture, drawOrder, priorityInput), font(font), str(), color{ 0, 0, 0, 0 }
{

}

void fontComponent::setFont(TTF_Font* fontInput)
{
	font = fontInput;
}

void fontComponent::setString(const std::string& string)
{
	str = string;
	if (texture != nullptr)
	{
		SDL_DestroyTexture(texture);
		texture = nullptr;
	}
}

void fontComponent::draw(SDL_Renderer* renderer)
{
	if (texture == nullptr && !str.empty())
	{
		auto surface = TTF_RenderText_Blended(font, str.c_str(), color);
		setTexture(SDL_CreateTextureFromSurface(renderer, surface));
		SDL_FreeSurface(surface);
	}
	spriteComponent::draw(renderer);//这个功能好
}

void fontComponent::serColor(const SDL_Color colorInput)
{
	color = colorInput;
}

