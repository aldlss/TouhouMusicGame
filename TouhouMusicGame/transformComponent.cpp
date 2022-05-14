#include "transformComponent.h"

transformComponent::transformComponent(baseGameObject* ownerInput, double x, double y, double z, int priorityInput)
	:baseComponent(ownerInput, priorityInput), position(x, y), z(z)
{
}