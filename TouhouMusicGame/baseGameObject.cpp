#include "baseGameObject.h"
#include "baseLever.h"

void baseGameObject::processInput(const Uint8* keyState)
{
	for (auto component : ownComponent)
		component->processInput(keyState);
}


baseGameObject::baseGameObject(baseLever* nowLever)
	:nowLever(nowLever), nowState(Alive)
{
	nowLever->createGameObject(this);
}

baseGameObject::~baseGameObject()
{
	while (!ownComponent.empty())
		delete ownComponent.back();
	nowLever->deleteGameObject(this);
}


void baseGameObject::update()
{
	for (auto component : ownComponent)
		component->update();
}

void baseGameObject::addComponent(baseComponent* willBeAddedComponent)
{
	auto pos = ownComponent.begin();
	int thisComponentPriority = willBeAddedComponent->getPriority();
	while (pos != ownComponent.end() && (*pos)->getPriority() < thisComponentPriority)
		++pos;
	ownComponent.insert(pos, willBeAddedComponent);
}

bool baseGameObject::removeComponent(baseComponent* willBeRemovedComponent)
{
	for (auto pos = ownComponent.begin(); pos != ownComponent.end(); ++pos)
		if (willBeRemovedComponent == *pos)
		{
			ownComponent.erase(pos);
			return true;
		}
	return false;
}
