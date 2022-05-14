#pragma once
#include "baseGameObject.h"
#include "spriteComponent.h"
#include <vector>
class overallGame
{
protected:
	std::vector<spriteComponent*>allSprite;
	std::vector<baseGameObject*>allGameObject;
public:
	void createGameObject(baseGameObject* willBeCreatedObject);
	bool deleteGameObject(baseGameObject* willBeDeletedObject);
	void addSprite(spriteComponent* willBeAddedComponent);
	bool removeSprite(spriteComponent* willBeRemovedComponent);

	void processInput();
	void update();
	void render();
};

