#include "noteComponent.h"
#include "baseLever.h"
#include "gameSetting.h"
#include "gameState.h"

noteComponent::noteComponent(baseGameObject* ownerInput, int track, SDL_Scancode beatKey, Uint32 beatTime, Uint32 endTime, category ownCategory, int priorityInput)
	:baseComponent(ownerInput, priorityInput), track(track), beatKey(beatKey), beatTime(beatTime), endTime(endTime), ownCategory(ownCategory), nowNoteState(Active)
{

}

noteComponent::~noteComponent()
{
	auto font = owner->getGame()->getTextObject("judgeText")->getComponent<fontComponent>();
	switch (nowNoteState)
	{
	case Miss:
		puts("MISS");
		font->setString(gameSetting::missStr);
		font->serColor(gameSetting::missColor);
		break;
	case Bad:
		puts("BAD");
		font->setString(gameSetting::badStr);
		font->serColor(gameSetting::badColor);
		break;
	case Good:
		puts("GOOD!");
		font->setString(gameSetting::greatStr);
		font->serColor(gameSetting::greatColor);
		break;
	case Perfect:
		puts("PERFECT!!");
		font->setString(gameSetting::perfectStr);
		font->serColor(gameSetting::perfectColor);
		break;
	case Active:
		puts("WHAT THE?");
		break;
	}
	font = owner->getGame()->getTextObject("comboText")->getComponent<fontComponent>();
	if (nowNoteState == Miss || nowNoteState == Bad)
	{
		font->setString("");
		gameState::combo = 0;
	}
	else
	{
		++gameState::combo;
		font->setString(std::to_string(gameState::combo).append(" " + gameSetting::comboStr));
		font->serColor(gameSetting::comboColor);
	}
}
