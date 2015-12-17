#include "CameraObject.h"

glm::vec3 CameraObject::getLocation()
{
	return position;
}

glm::vec3 CameraObject::getForward()
{
	float fx = cos(pitch)*sin(yaw);
	float fy = sin(pitch);
	//might not have the negative
	float fz = cos(pitch)*cos(yaw);
	return glm::vec3(fx, fy, fz);
}

glm::vec3 CameraObject::getOneAhead()
{
	return getLocation() + getForward();
}

glm::vec3 CameraObject::getUp()
{
	//could also do glm::vec3 up = glm::cross(right, forward)

	/*float fx = cos(pitch + 90)*sin(yaw);
	float fy = sin(pitch + 90);
	float fz = -cos(pitch + 90)*cos(yaw);
	return glm::vec3(fx, fy, fz);*/

	return glm::cross(getRight(), getForward());
}

glm::vec3 CameraObject::getRight()
{
	/*
	also
	glm::vec3( sin(yaw - (M_PI/2.0f)), 0, cos(yaw - (M_PI/2.0f)) )
	*/

	//return glm::cross( getUp(), getForward() );
	return glm::vec3(sin(yaw - (M_PI / 2.0f)), 0, cos(yaw - (M_PI / 2.0f)));
}

float CameraObject::getFoV()
{
	return fov;
}

void CameraObject::setFoV(float fov)
{
	this->fov = fov;
}

CameraObject::CameraObject()
{
	position = glm::vec3(0, 0, 1);
	yaw = 3.14f;
	pitch = 0.0f;
	fov = 45.0f;

	//in case
	speed = 3.0f;
	mouseSpeed = 0.005f;
}

CameraObject::CameraObject(const CameraObject& cameraObjectCopy)
{
}

CameraObject::~CameraObject()
{
}

void CameraObject::turn(float dx, float dy)
{
	yaw -= dx;
	//limit pitch to prevent gimbal lock
	if ((pitch > -90 && pitch - dy > -90) || (pitch < 90 && pitch - dy < 90))
		pitch -= dy;
	else if (pitch < -90 && pitch - dy < -90)
		pitch = -90;
	else if (pitch > 90 && pitch - dy > 90)
		pitch = 90;
}