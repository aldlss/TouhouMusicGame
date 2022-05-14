#include "overallGame.h"


void overallGame::addSprite(spriteComponent* willBeAddedComponent)
{
	auto pos = allSprite.begin();
	int thisComponent = willBeAddedComponent->();
	while (pos != allSprite.end() && (*pos)->getDrawOrder() < thisComponent)
		++pos;
	allSprite.insert(pos, willBeAddedComponent);
}

bool overallGame::removeSprite(spriteComponent* willBeRemovedComponent)
{
	for (auto pos = allSprite.begin(); pos != allSprite.end(); ++pos)
		if (willBeRemovedComponent == *pos)
		{
			allSprite.erase(pos);
			return true;
		}
	return false;
}

void overallGame::createGameObject(baseGameObject* willBeCreatedObject)
{
	allGameObject.emplace_back(willBeCreatedObject);
}

bool overallGame::deleteGameObject(baseGameObject* willBeDeletedObject)
{
	auto pos = std::ranges::find(allGameObject, willBeDeletedObject);
	if (pos == allGameObject.end())return false;
	std::iter_swap(pos, allGameObject.end() - 1);
	allGameObject.pop_back();
	return true;
}
