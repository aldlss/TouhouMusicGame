#include "baseGameObject.h"

baseGameObject::baseGameObject(overallGame* nowGame)
{
	nowGame->createGameObject(this);
}

baseGameObject::~baseGameObject()
{
	while (!ownComponent.empty())
		delete ownComponent.back();
	nowGame->deleteGameObject(this);
}


void baseGameObject::update()
{
	for (auto component : ownComponent)
		component->update();
}

void baseGameObject::addComponent(baseComponent* willBeAddedComponent)
{
	auto pos = ownComponent.begin();
	int thisComponent = willBeAddedComponent->getPriority();
	while (pos != ownComponent.end() && (*pos)->getPriority() < thisComponent)
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
