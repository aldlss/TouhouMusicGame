#pragma once
#include "baseGameObject.h"
#include "trackComponent.h"
class trackObject :
	public baseGameObject
{
protected:
	trackComponent* track;
	transformComponent* transform;
	spriteComponent* sprite;
public:
	trackObject(baseLever* nowLever, std::queue<musicalNote::NodeInfo>&& waitingTrack, double x, double y, double z, SDL_Texture* texture, int drawOrde);
	static trackObject* createCrackObjectSimple(baseLever* nowLever, std::queue<musicalNote::NodeInfo>&& waitingTrack);
};