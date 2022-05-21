#include "trackObject.h"
#include "gameSetting.h"
#include "baseLever.h"

trackObject::trackObject(baseLever* nowLever, std::queue<musicalNote::NodeInfo>&& waitingTrack, double x, double y, double z, SDL_Texture* texture, int drawOrder)
	:baseGameObject(nowLever)
{
	track = new trackComponent(this, std::move(waitingTrack));
	transform = new transformComponent(this, x, y, z);
	sprite = new spriteComponent(this, texture, drawOrder);
}

trackObject* trackObject::createCrackObjectSimple(baseLever* nowLever, std::queue<musicalNote::NodeInfo>&& waitingTrack)
{
	auto temp = new trackObject(nowLever, std::move(waitingTrack), gameSetting::standardX, gameSetting::standardY, 0, nowLever->getTexture("roundTrack"), 50);
	temp->getComponent<transformComponent>()->setScale(0.5, 0.5, 1);
	return temp;
}
