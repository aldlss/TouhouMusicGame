#include "noteComponent.h"

noteComponent::noteComponent(baseGameObject* ownerInput, int track, SDL_Scancode beatKey, Uint32 beatTime, Uint32 endTime, category ownCategory, int priorityInput)
	:baseComponent(ownerInput, priorityInput), track(track), beatKey(beatKey), beatTime(beatTime), endTime(endTime), ownCategory(ownCategory), nowNoteState(Active)
{

}

noteComponent::~noteComponent()
{
	switch (nowNoteState)
	{
	case Miss:
		puts("MISS");
		break;
	case Bad:
		puts("BAD");
		break;
	case Good:
		puts("GOOD!");
		break;
	case Perfect:
		puts("PERFECT!!");
		break;
	case Active:
		puts("WHAT THE?");
		break;
	}
}
