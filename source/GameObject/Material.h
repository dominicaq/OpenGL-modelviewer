#ifndef MATERIAL_H
#define MATERIAL_H

#include "Shader.h"
#include "Texture.h"
#include <vector>

struct Material
{
    Vector3 color = Vector3(2, 2, 2);
    Vector3 ambient = Vector3(1.0f, 0.5f, 0.31f);
    Vector3 diffuse = Vector3(1.0f, 0.5f, 0.31f);
    Vector3 specular = Vector3(0.5f, 0.5f, 0.5f);
    float shininess = 32;
};

#endif