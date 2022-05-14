#include "noteComponent.h"

noteComponent::noteComponent(baseGameObject* ownerInput, SDL_Scancode beatKey, Uint32 beatTime, Uint32 endTime, int priorityInput)
	:baseComponent(ownerInput, priorityInput), beatKey(beatKey), beatTime(beatTime), endTime(endTime)
{

}

