#ifndef MESH_H
#define MESH_H

#include "Shader.h"

#include <glm/glm.hpp>
#include <array>
#include <vector>

struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
};

enum TextureType { DIFFUSE, SPECULAR };
// NOTE: Must match the number of elements in the above struct
constexpr int TextureTypeNum = 2;
// NOTE: Add new cases when adding new types
inline std::string TextureType_toString (TextureType tt) {
    switch (tt) {
        case DIFFUSE: return "texture_diffuse";
        case SPECULAR: return "texture_specular";
        default: throw std::invalid_argument ("Unimplemented texture type");
    }
}

struct Texture {
    unsigned int id;
    TextureType type;
};

class Mesh {
public:
    Mesh (std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);

    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;

    void draw (Shader &shader);
private:
    unsigned int VAO, VBO, EBO;
};

#endif
