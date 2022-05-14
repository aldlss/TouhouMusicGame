#ifndef _BASE_COMPONENT_
#define _BASE_COMPONENT_
#include "baseGameObject.h"
class baseGameObject;
class baseComponent
{
protected:
	baseGameObject* owner;
	int priority;
public:
	virtual ~baseComponent();
	virtual void update();
	baseComponent(baseGameObject* ownerInput, int priorityInput = 0);
	int getPriority() const;
};
#endif //_BASE_COMPONENT_
