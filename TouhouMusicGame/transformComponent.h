#ifndef _TRANS_COMPON_
#define _TRANS_COMPON_
#include "baseComponent.h"
#include "Eigen/Dense"
#include <tuple>
class transformComponent :
	public baseComponent
{
protected:
	Eigen::Vector2<double>position;
	double z;//单独独立出来，因为这个是不经常用到的

public:
	//默认优先级为50
	transformComponent(baseGameObject* ownerInput, double x = 0, double y = 0, double z = 0, int priorityInput = 50);
};

#endif //_TRANS_COMPON_