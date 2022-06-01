#include "imgObject.h"
imgObject::imgObject(baseLever* nowLever)
	:baseGameObject(nowLever)
{
	sprite = new spriteComponent(this, nullptr, 10);
	transform = new transformComponent(this);
	transformChange = new transformChangeComponent(this);
}
