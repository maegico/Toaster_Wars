#ifndef CAMERAOBJECT_H
#define CAMERAOBJECT_H

#include "GameObject.h"
class CameraObject :
	public GameObject
{
public:
	float yaw;
	float pitch;

	glm::vec3 getLocation();
	glm::vec3 getForward();
	glm::vec3 getLookAt();
	glm::vec3 getUp();
	glm::vec3 getRight();

	CameraObject();
	CameraObject(const CameraObject& cameraObjectCopy);
	~CameraObject();

	void turn(float dx, float dy);
};

#endif