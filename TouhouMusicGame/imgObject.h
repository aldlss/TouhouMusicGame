#pragma once
#include "baseGameObject.h"
#include "spriteComponent.h"
#include "transformComponent.h"
#include "transformChangeComponent.h"
class imgObject :
	public baseGameObject
{
	spriteComponent* sprite;
	transformComponent* transform;
	transformChangeComponent* transformChange;
public:
	imgObject(baseLever* nowLever);
};

