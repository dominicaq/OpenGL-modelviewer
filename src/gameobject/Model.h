#ifndef MODEL_H
#define MODEL_H

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "standardMath.h"

#include "../gameobject/Transform.h"
#include "../gameobject/Mesh.h"
#include "Camera.h"

#include <iostream>

class Model
{
public:
    Transform transform;
    std::vector<Mesh> meshes;
    std::vector<Texture>textures;
    
    void Draw(Camera& cam, Shader& shader);

    void loadModel(std::string path);
    void DeleteModel();

    void operator=(const Model& model);
};

#endif