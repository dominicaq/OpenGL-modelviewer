#ifndef ENTITY_H
#define ENTITY_H

#include "GameObject/Transform.h"
#include "GameObject/Shader.h"
#include "Model.h"

class Entity
{
	Transform transform;
	Shader shader;
	Model model;

};

#endif