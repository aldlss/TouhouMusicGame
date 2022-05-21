#include "textObject.h"
textObject::textObject(baseLever* nowLever, TTF_Font* font, SDL_Texture* texture, double x, double y, double z, int drawOrder)
	:baseGameObject(nowLever)
{
	fontComponent = new ::fontComponent(this, font, texture, drawOrder);
	transformComponent = new ::transformComponent(this, x, y, z);
}
