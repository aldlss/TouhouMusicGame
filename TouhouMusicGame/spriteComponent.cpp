#include "spriteComponent.h"
#include "transformComponent.h"
#include "someTools.h"
#include "baseLever.h"
spriteComponent::spriteComponent(baseGameObject* ownerInput, SDL_Texture* texture, int drawOrder, int priorityInput)
	: baseComponent(ownerInput, priorityInput), texture(texture), drawOrder(drawOrder), textureWidth(0), textureHeight(0)
{
	ownerInput->getGame()->addSprite(this);
	SDL_QueryTexture(texture, nullptr, nullptr, &textureWidth, &textureHeight);
}

spriteComponent::~spriteComponent()
{
	owner->getGame()->removeSprite(this);
}

void spriteComponent::setTexture(SDL_Texture* textureInput)//这里加inline会报错，我猜是他子类font在另一个函数调用了它的原因
{
	texture = textureInput;
	SDL_QueryTexture(texture, nullptr, nullptr, &textureWidth, &textureHeight);
}

void spriteComponent::draw(SDL_Renderer* renderer)
{
	auto transform = owner->getComponent<transformComponent>();
	SDL_Rect dst(transform->getPosition()[0], transform->getPosition()[1], textureWidth * transform->getScale()[0], textureHeight * transform->getScale()[1]);
	someTools::RenderCopyExByCenter(renderer, texture, nullptr, &dst, transform->getRotation()[0], nullptr, SDL_FLIP_NONE);
}
