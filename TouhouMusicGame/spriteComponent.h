#pragma once
#include "baseComponent.h"
#include "SDL2/SDL.h"
class baseComponent;
class spriteComponent :
	public baseComponent
{
public:
	spriteComponent(baseGameObject* ownerInput, SDL_Texture* texture = nullptr, int drawOrder = 50, int priorityInput = 100);
	~spriteComponent();
	int getDrawOrder()const { return drawOrder; }
	void draw(SDL_Renderer* renderer);
	void setTexture(SDL_Texture* textureInput);
protected:
	SDL_Texture* texture;
	int drawOrder;
	int textureWidth;
	int textureHeight;
};

