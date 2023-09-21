#ifndef MESH_H
#define MESH_H

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "standardMath.h"

#include "../gameobject/Transform.h"
#include "Material.h"
#include "Shader.h"
#include "Camera.h"

#include <string>
#include <vector>

struct Vertex {
	Vector3 position;
	Vector2 texCoord;
	Vector3 normal;
	Vector3 color;
};

class Mesh
{
public:
	Material material;
	//Texture texture;

	GLuint VAO;
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;

	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices);
	
	void Draw(Camera& camera, Transform& transform, Shader& shader);
	void ClearBuffers();
	
private:
	void genMesh();

	enum
	{
		VERTEX_POSITIONS,
		VERTEX_TEXTURE_COORDS,
		VERTEX_NORMALS,
		VERTEX_COLORS
	};

	GLuint m_VBO, m_EBO;
};
#endif