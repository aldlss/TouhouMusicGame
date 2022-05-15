#include "transformChangeComponent.h"
#include "transformComponent.h"
#include "timer.h"
transformChangeComponent::transformChangeComponent(baseGameObject* ownerInput, double vX, double vY, double vZ, double aX, double aY, double aZ, int priorityInput)
	:baseComponent(ownerInput, priorityInput), velocity(vX, vY, vZ), acceleration(aX, aY, aZ), scaleVelocity(0, 0, 0), scaleAcceleration(0, 0, 0), rotationVelocity(0, 0, 0), rotationAcceleration(0, 0, 0)
{
}

void transformChangeComponent::update()
{
	auto transform = owner->getComponent<transformComponent>();
	if (transform == nullptr)return;
	transform->increaseDeltaPosition((velocity * 2 + acceleration) * timer::deltaTime / 2.0);
	velocity += acceleration * timer::deltaTime;
	transform->increaseDeltaScale((scaleVelocity * 2 + scaleAcceleration) * timer::deltaTime / 2.0);//我谔谔啊，少加了一个上底
	scaleVelocity += scaleAcceleration * timer::deltaTime;
	transform->increaseDeltaPosition((rotationVelocity * 2 + rotationAcceleration) * timer::deltaTime / 2.0);
	rotationVelocity += rotationAcceleration * timer::deltaTime;
}
