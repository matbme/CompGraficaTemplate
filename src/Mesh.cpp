#include "Mesh.h"

// Mesh::Mesh (std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures) {
//     this->vertices = vertices;
//     this->indices = indices;
//     this->textures = textures;
//
// }

void Mesh::setup () {
    // Setup mesh
    glGenVertexArrays (1, &VAO);
    glGenBuffers (1, &VBO);
    glGenBuffers (1, &EBO);

    glBindVertexArray (VAO);
    glBindBuffer (GL_ARRAY_BUFFER, VBO);
    glBufferData (GL_ARRAY_BUFFER,
                  this->vertices.size () * sizeof (Vertex),
                  &this->vertices[0],
                  GL_STATIC_DRAW);

    glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData (GL_ELEMENT_ARRAY_BUFFER,
                  this->indices.size () * sizeof (unsigned int),
                  &this->indices[0],
                  GL_STATIC_DRAW);

    // Vertex pos
    glEnableVertexAttribArray (0);
    glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE,
                           sizeof (Vertex), (void *) 0);

    // Vertex normals
    glEnableVertexAttribArray (1);
    glVertexAttribPointer (1, 3, GL_FLOAT, GL_FALSE,
                           sizeof (Vertex), (void *) offsetof (Vertex, Normal));

    // Vertex texture coords
    // glEnableVertexAttribArray (2);
    // glVertexAttribPointer (2, 2, GL_FLOAT, GL_FALSE,
    //                        sizeof (Vertex), (void *) offsetof (Vertex, TexCoords));

    glBindVertexArray (0);
}

void Mesh::draw () {
    std::array<int, TextureTypeNum> textureType_number = { 0 };
    int texture_number = GL_TEXTURE0;

    // for (auto texture : textures) {
    //     glActiveTexture (texture_number++);
    //
    //     textureType_number[texture.type]++;
    //
    //     shader.setFloat(
    //         ("material." +
    //         TextureType_toString (texture.type) +
    //         std::to_string (textureType_number[texture.type])
    //         ).c_str (),
    //         texture_number - GL_TEXTURE0
    //     );
    //
    //     glBindTexture (GL_TEXTURE_2D, texture.id);
    // }
    // glActiveTexture (GL_TEXTURE0);

    glBindVertexArray (VAO);
    glDrawElements (GL_TRIANGLES, indices.size (), GL_UNSIGNED_INT, 0);
    glBindVertexArray (0);
}
