#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

#include "Model.h"

void Model::loadModel(std::string modelPath)
{
    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;

    std::string warn, err;

    if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, modelPath.c_str())) {
        std::cout << warn << err << std::endl;
    }

    for (size_t s = 0; s < shapes.size(); s++)
    {
        size_t index_offset = 0;
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;

        for (size_t f = 0; f < shapes[s].mesh.indices.size(); f++)
        {
            tinyobj::index_t index = shapes[s].mesh.indices[index_offset + f];
            Vertex vertex;

            vertex.position = {
                attrib.vertices[3 * index.vertex_index + 0],
                attrib.vertices[3 * index.vertex_index + 1],
                attrib.vertices[3 * index.vertex_index + 2]
            };

            vertex.texCoord = {
                attrib.texcoords[2 * index.texcoord_index + 0],
                attrib.texcoords[2 * index.texcoord_index + 1]
            };
                        
            vertex.normal = {
                attrib.normals[3 * index.normal_index + 0],
                attrib.normals[3 * index.normal_index + 1],
                attrib.normals[3 * index.normal_index + 2],
            };

            vertex.color = {
                attrib.colors[3 * index.vertex_index + 0],
                attrib.colors[3 * index.vertex_index + 1],
                attrib.colors[3 * index.vertex_index + 2],
            };

            vertices.push_back(vertex);
            indices.push_back(indices.size());
        }

        
        meshes.push_back(Mesh(vertices, indices));
    }
}

void Model::Draw(Camera& cam, Shader& shader)
{
    for (int i = 0; i < meshes.size(); i++)
    {
        if (i < textures.size())
        {
            textures[0].Bind(0);
        }

        meshes[i].Draw(cam, transform, shader);
    }
}

void Model::operator=(const Model& model)
{
    this->meshes = model.meshes;
    this->textures = model.textures;
}

void Model::DeleteModel()
{
    for (int i = 0; i < textures.size(); i++)
        textures[i].ClearTexture();

    for (int i = 0; i < meshes.size(); i++)
        meshes[i].ClearBuffers();
}