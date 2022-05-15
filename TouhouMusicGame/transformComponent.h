#ifndef _TRANS_COMPON_
#define _TRANS_COMPON_
#include "baseComponent.h"
#include "Eigen/Dense"
#include <tuple>
class transformComponent :
	public baseComponent
{
protected:
	Eigen::Vector3d position;//全部3d，不管了（
	// double z;//单独独立出来，因为这个是不经常用到的

	Eigen::Vector3d scale;
	Eigen::Vector3d rotation;//XY XZ YZ

public:
	//默认优先级为50
	transformComponent(baseGameObject* ownerInput, double x = 0, double y = 0, double z = 0, int priorityInput = 50);

	void setPositionX(double x) { position[0] = x; }
	void setPositionY(double y) { position[1] = y; }
	void setPositionZ(double z) { position[2] = z; }
	void setPosition(double x, double y, double z) { position = { x,y,z }; }
	void increaseDeltaPosition(double dx, double dy, double dz) { position = { dx,dy,dz }; }
	void increaseDeltaPosition(Eigen::Vector3d delta) { position += delta; }
	Eigen::Vector3d getPosition() const { return position; }

	void setScaleX(double x) { scale[0] = x; }
	void setScaleY(double y) { scale[1] = y; }
	void setScaleZ(double z) { scale[2] = z; }
	void setScale(double x, double y, double z) { scale = { x,y,z }; }
	void increaseDeltaScale(Eigen::Vector3d delta) { scale += delta; }
	Eigen::Vector3d getScale()const { return scale; }

	void setRotationXY(double XY) { rotation[0] = XY; }
	void setRotationXZ(double XZ) { rotation[1] = XZ; }
	void setRotationYZ(double YZ) { rotation[2] = YZ; }
	void increaseDeltaRotation(Eigen::Vector3d delta) { rotation += delta; }
	void setRotation(double XY, double XZ, double YZ) { rotation = { XY,XZ,YZ }; }
	Eigen::Vector3d getRotation() const { return rotation; }
};

#endif //_TRANS_COMPON_