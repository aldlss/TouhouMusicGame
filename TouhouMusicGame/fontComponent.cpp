#include "fontComponent.h"
#include "someTools.h"
#include "baseLever.h"
#include "transformComponent.h"
fontComponent::fontComponent(baseGameObject* ownerInput, TTF_Font* font, SDL_Texture* texture, int drawOrder, int priorityInput)
	:spriteComponent(ownerInput, texture, drawOrder, priorityInput), font(font), str(), color{ 0, 0, 0, 0 }
{

}

fontComponent::~fontComponent()
{
	if (texture != nullptr)
		SDL_DestroyTexture(texture);
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
		SDL_DestroyTexture(texture);//这里要这样写的原因，是因为这里texture都是自己造的，不像父类一样是别人给的，所以要自己处理
		texture = nullptr;
	}
}

void fontComponent::draw(SDL_Renderer* renderer)
{
	if (texture == nullptr && !str.empty())
	{
		auto surface = TTF_RenderUTF8_Blended(font, str.c_str(), color);
		setTexture(SDL_CreateTextureFromSurface(renderer, surface));
		SDL_FreeSurface(surface);
	}
	spriteComponent::draw(renderer);//这个功能好
}

void fontComponent::serColor(const SDL_Color colorInput)
{
	color = colorInput;
}

