#pragma once
#include "baseComponent.h"
#include "Eigen/Dense"
class transformChangeComponent :
	public baseComponent
{
protected:
	Eigen::Vector3d velocity;
	Eigen::Vector3d acceleration;
	Eigen::Vector3d scaleVelocity;
	Eigen::Vector3d scaleAcceleration;
	Eigen::Vector3d rotationVelocity;
	Eigen::Vector3d rotationAcceleration;
	void update() override;
public:
	transformChangeComponent(baseGameObject* ownerInput, double vX = 0, double vY = 0, double vZ = 0, double aX = 0, double aY = 0, double aZ = 0, int priorityInput = 30);

	void setVelocityX(double x) { velocity[0] = x; }
	void setVelocityY(double y) { velocity[1] = y; }
	void setVelocityZ(double z) { velocity[2] = z; }
	void setVelocity(double x, double y, double z) { velocity = { x,y,z }; }
	Eigen::Vector3d getVelocity() const { return velocity; }

	void setAccelerationX(double x) { acceleration[0] = x; }
	void setAccelerationY(double y) { acceleration[1] = y; }
	void setAccelerationZ(double z) { acceleration[2] = z; }
	void setAcceleration(double x, double y, double z) { acceleration = { x,y,z }; }
	Eigen::Vector3d getAcceleration() const { return acceleration; }

	void setScaleVelocityX(double x) { scaleVelocity[0] = x; }
	void setScaleVelocityY(double y) { scaleVelocity[1] = y; }
	void setScaleVelocityZ(double z) { scaleVelocity[2] = z; }
	void setScaleVelocity(double x, double y, double z) { scaleVelocity = { x,y,z }; }
	Eigen::Vector3d getScaleVelocity() const { return scaleVelocity; }

	void setScaleAccelerationX(double x) { scaleAcceleration[0] = x; }
	void setScaleAccelerationY(double y) { scaleAcceleration[1] = y; }
	void setScaleAccelerationZ(double z) { scaleAcceleration[2] = z; }
	void setScaleAcceleration(double x, double y, double z) { scaleAcceleration = { x,y,z }; }
	Eigen::Vector3d getScaleAcceleration() const { return scaleAcceleration; }

	void setRotationVelocityX(double x) { rotationVelocity[0] = x; }
	void setRotationVelocityY(double y) { rotationVelocity[1] = y; }
	void setRotationVelocityZ(double z) { rotationVelocity[2] = z; }
	void setRotationVelocity(double x, double y, double z) { rotationVelocity = { x,y,z }; }
	Eigen::Vector3d getRotationVelocity() const { return rotationVelocity; }

	void setRotationAccelerationXY(double xy) { rotationAcceleration[0] = xy; }
	void setRotationAccelerationXZ(double xz) { rotationAcceleration[1] = xz; }
	void setRotationAccelerationYZ(double yz) { rotationAcceleration[2] = yz; }
	void setRotationAcceleration(double xy, double xz, double yz) { rotationAcceleration = { xy,xz,yz }; }
	Eigen::Vector3d getRotationAcceleration() const { return rotationAcceleration; }

	void setAllVelocity(Eigen::Vector3d&& velocityInput, Eigen::Vector3d&& scaleVelocityInput, Eigen::Vector3d&& rotationVelocityInput) {
		velocity = velocityInput;
		scaleVelocity = scaleVelocityInput;
		rotationVelocity = rotationVelocityInput;
	}

	void setAllAcceleration(Eigen::Vector3d&& accelerationInput, Eigen::Vector3d&& scaleAccelerationInput, Eigen::Vector3d&& rotationAccelerationInput) {
		acceleration = accelerationInput;
		scaleAcceleration = scaleAccelerationInput;
		rotationAcceleration = rotationAccelerationInput;
	}

	void setAll(Eigen::Vector3d&& velocityInput, Eigen::Vector3d&& scaleVelocityInput, Eigen::Vector3d&& rotationVelocityInput,
		Eigen::Vector3d&& accelerationInput, Eigen::Vector3d&& scaleAccelerationInput, Eigen::Vector3d&& rotationAccelerationInput)
	{
		velocity = velocityInput;
		scaleVelocity = scaleVelocityInput;
		rotationVelocity = rotationVelocityInput;
		acceleration = accelerationInput;
		scaleAcceleration = scaleAccelerationInput;
		rotationAcceleration = rotationAccelerationInput;
	}
};

