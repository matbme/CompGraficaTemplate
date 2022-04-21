#ifndef MESH_H
#define MESH_H

#include "Shader.h"

#include <glm/glm.hpp>
#include <array>
#include <memory>
#include <vector>

struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
};
constexpr bool operator==(const Vertex& lhs, const Vertex& rhs) {
    return lhs.Position  == rhs.Position   &&
           lhs.Normal    == rhs.Normal     &&
           lhs.TexCoords == rhs.TexCoords;
}

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
    // Mesh (std::vector<Vertex> vertices,
    //       std::vector<unsigned int> indices,
    //       std::vector<Texture> textures);
    Mesh () {}

    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;

    void setup ();
    void draw ();

    void setShader (Shader *shader) {
        this->shader = shader;
        shader->Use ();
    }
private:
    Shader *shader;
    unsigned int VAO, VBO, EBO;
};

#endif
