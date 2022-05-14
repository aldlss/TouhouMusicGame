#include "baseComponent.h"

baseComponent::baseComponent(baseGameObject* ownerInput, int priorityInput)
	:owner(ownerInput), priority(priorityInput)
{
	owner->addComponent(this);
}

void baseComponent::update()
{

}


baseComponent::~baseComponent()
{
	owner->removeComponent(this);
}

int baseComponent::getPriority() const
{
	return priority;
}