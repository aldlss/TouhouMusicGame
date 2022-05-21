#pragma once
#include "baseGameObject.h"
#include "fontComponent.h"
#include "transformComponent.h"
class textObject :
	public baseGameObject
{
protected:
	fontComponent* fontComponent;
	transformComponent* transformComponent;
public:
	textObject(baseLever* nowLever, TTF_Font* font, SDL_Texture* texture, double x, double y, double z, int drawOrder);
	// static textObject* createTextObjectSimple(baseLever* nowLever, TTF_Font* font)
};

