#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"
#include <glm/gtx/quaternion.hpp>

class Transform
{
public:
	Vector3 forward = Vector3(0, 0, -1);
	Vector3 up = Vector3(0, 1, 0);
	Vector3 zero = Vector3(0, 0, 0);

	Vector3 scale;
	Vector3 position;
	Vector3 eulerAngles;

	Transform(const Vector3& position = Vector3(), const Vector3& eulerAngles = Vector3(), const Vector3& scale = Vector3(1.0f, 1.0f, 1.0f))
	{
		this->position = position;
		this->scale = scale;
		this->eulerAngles = eulerAngles;
	}

	inline Matrix4 GetModelMatrix() const
	{
		Matrix4 rotMatrix(1.0);
		rotMatrix = glm::rotate(rotMatrix, glm::radians(eulerAngles.x), Vector3(1, 0, 0));
		rotMatrix = glm::rotate(rotMatrix, glm::radians(eulerAngles.y), Vector3(0, 1, 0));
		rotMatrix = glm::rotate(rotMatrix, glm::radians(eulerAngles.z), Vector3(0, 0, 1));

		Matrix4 scaleMatrix = glm::scale(scale);
		Matrix4 posMatrix = glm::translate(Matrix4(1.0), position);

		return posMatrix * rotMatrix * scaleMatrix;
	}
};

#endif