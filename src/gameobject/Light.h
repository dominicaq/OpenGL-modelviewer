#ifndef LIGHT_H
#define LIGHT_H

#include "GameObject/Transform.h"

struct Light {
	Transform transform;
	float intesnity;
	Vector3 color;
};

#endif