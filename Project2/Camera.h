#ifndef CAMERA_H
#define CAMERA_H

#include "Maths/glm.h"
#include <glm/gtx/euler_angles.hpp>
#include "GameObject/Transform.h"

class Camera
{
public:
	float fov;
	float zNear, zFar;

	Transform transform;

	Camera(float fov, float zNear, float zFar)
	{
		this->fov = fov;
		this->zNear = zNear;
		this->zFar = zFar;
	}
	
	inline Matrix4 GetPerspectiveMatrix() const
	{
		const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
		float aspectRatio = (float)mode->width / (float)mode->height;
		return glm::perspective(glm::radians(fov), aspectRatio, zNear, zFar);
	}

	inline Matrix4 GetViewMatrix() const
	{
		Matrix4 xRotMatrix = glm::rotate(glm::radians(transform.eulerAngles.x), Vector3(1, 0, 0));
		Matrix4 yRotMatrix = glm::rotate(glm::radians(transform.eulerAngles.y), Vector3(0, 1, 0));
		Matrix4 zRotMatrix = glm::rotate(glm::radians(transform.eulerAngles.z), Vector3(0, 0, 1));
		Matrix4 rotMatrix = zRotMatrix * yRotMatrix * xRotMatrix;

		Matrix4 posMatrix = glm::translate(Matrix4(1.0), -transform.position);
		return rotMatrix * posMatrix;
	}
};
#endif