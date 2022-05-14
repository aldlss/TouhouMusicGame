#pragma once
#include "baseComponent.h"
#include "SDL2/SDL.h"
class spriteComponent :
	public baseComponent
{
public:
	spriteComponent(baseGameObject* ownerInput, int drawOrder = 50, int priorityInput = 100);
	~spriteComponent();
	int getDrawOrder()const { return drawOrder; }
protected:
	SDL_Texture* texture;
	int drawOrder;
	int textureWidth;
	int textureHeight;
};

