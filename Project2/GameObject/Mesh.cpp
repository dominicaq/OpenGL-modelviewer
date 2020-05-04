#include "Mesh.h"
#include <iostream> // DEBUG

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices)
{
    this->vertices = vertices;
    this->indices = indices;

    genMesh();
}

void Mesh::genMesh()
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &m_VBO);
    glGenBuffers(1, &m_EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

    // vertex Positions
    glEnableVertexAttribArray(VERTEX_POSITIONS);
    glVertexAttribPointer(VERTEX_POSITIONS, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

    // vertex texture coords
    glEnableVertexAttribArray(VERTEX_TEXTURE_COORDS);
    glVertexAttribPointer(VERTEX_TEXTURE_COORDS, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoord));

    // vertex Normals
    glEnableVertexAttribArray(VERTEX_NORMALS);
    glVertexAttribPointer(VERTEX_NORMALS, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));

    // vertex Color
    glEnableVertexAttribArray(VERTEX_COLORS);
    glVertexAttribPointer(VERTEX_COLORS, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));

    glBindVertexArray(0);
}

void Mesh::Draw(Camera& camera, Transform& transform, Shader& shader)
{
    shader.setMat4("model", transform.GetModelMatrix());
    shader.setMat4("view", camera.GetViewMatrix());
    shader.setMat4("projection", camera.GetPerspectiveMatrix());

    shader.Bind();

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void Mesh::ClearBuffers()
{
    glDeleteBuffers(1, &m_VBO);
    glDeleteBuffers(1, &m_EBO);
    glDeleteVertexArrays(1, &VAO);
}