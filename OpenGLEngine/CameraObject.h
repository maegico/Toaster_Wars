#ifndef CAMERAOBJECT_H
#define CAMERAOBJECT_H

#define _USE_MATH_DEFINES

#include <cmath>
#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>

class CameraObject
{
public:
	glm::vec3 position;
	//horizontal angle
	float yaw;
	//vertical angle
	float pitch;
	float fov;

	//in case
	float speed;
	float mouseSpeed;

	glm::vec3 getLocation();
	glm::vec3 getForward();
	glm::vec3 getOneAhead();
	glm::vec3 getUp();
	glm::vec3 getRight();
	float getFoV();
	void setFoV(float fov);

	CameraObject();
	CameraObject(const CameraObject& cameraObjectCopy);
	~CameraObject();

	void turn(float dx, float dy);
};

#endif