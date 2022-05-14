#include "spriteComponent.h"

spriteComponent::spriteComponent(baseGameObject* ownerInput, int drawOrder, int priorityInput)
	:baseComponent(ownerInput, priorityInput), drawOrder(drawOrder)
{
	ownerInput->getGame()->addSprite(this);
}

spriteComponent::~spriteComponent()
{
	owner->getGame()->removeSprite(this);
}
