#include "Mesh.h"

Mesh::Mesh () {
    model = glm::mat4 (1);
    pos = glm::vec3 (0.0f, 0.0f, 0.0f);
    scale = glm::vec3 (1.0f, 1.0f, 1.0f);
    angle = 0.0f;
    highlight = false;
}


std::map<std::string, unsigned int> Mesh::loaded_tex_rel_path;

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
    glEnableVertexAttribArray (2);
    glVertexAttribPointer (2, 2, GL_FLOAT, GL_FALSE,
                           sizeof (Vertex), (void *) offsetof (Vertex, TexCoords));

    glBindVertexArray (0);
}

void Mesh::draw () {
    if (!textures.empty()) {
        std::array<int, TextureTypeNum> textureType_number = { 0 };
        int texture_number = GL_TEXTURE0;

        for (auto texture : textures) {
            glActiveTexture (texture_number++);

            textureType_number[texture.type]++;

            /* shader->setFloat( */
            /*     ("material." + */
            /*     TextureType_toString (texture.type) + */
            /*     std::to_string (textureType_number[texture.type]) */
            /* ).c_str (), */
            /*     texture_number - GL_TEXTURE0 */
            /* ); */

            glBindTexture (GL_TEXTURE_2D, texture.id);
        }

        glUniform1i (glGetUniformLocation (shader->ID, "isTextured"), 1);
        glActiveTexture (GL_TEXTURE0);
    }
    else {
        glUniform1i (glGetUniformLocation (shader->ID, "isTextured"), 0);
        glBindTexture (GL_TEXTURE_2D, 0);
        glActiveTexture (0);

        if (this->material != nullptr)
            this->shader->setVec3 ("material.untex_diffuse", this->material->get_diffuse_refl ());
    }

    if (highlight) glUniform1i (glGetUniformLocation (shader->ID, "texHighlight"), 1);
    else glUniform1i (glGetUniformLocation (shader->ID, "texHighlight"), 0);

    if (this->material != nullptr) {
        this->shader->setVec3 ("material.ambient", this->material->get_ambient_refl ());
        this->shader->setVec3 ("material.specular", this->material->get_specular_refl ());
        this->shader->setFloat ("material.intensity", this->material->get_specular_exp ());
        this->shader->setFloat ("material.illum", this->material->get_illum ());
    }

    glBindVertexArray (VAO);
    glDrawElements (GL_TRIANGLES, indices.size (), GL_UNSIGNED_INT, 0);
    glBindVertexArray (0);
}

void Mesh::setShader (std::shared_ptr<Shader> shader) {
    this->shader = shader;
    shader->Use ();
}

void Mesh::rotate (float angle, glm::vec3 axis, bool reset) {
    if (reset) model = glm::mat4 (1);
    model = glm::rotate (model, angle, axis);
    this->angle += angle;
}

void Mesh::translate (glm::vec3 displacements, bool reset) {
    if (reset) model = glm::mat4 (1);
    model = glm::translate (model, displacements);
    this->pos += displacements;
}

void Mesh::rescale (glm::vec3 scaleFactors, bool reset) {
    if (reset) model = glm::mat4 (1);
    model = glm::scale (model, scaleFactors);
    this->scale += scaleFactors;
}

void Mesh::update () {
    GLint modelLoc = glGetUniformLocation (shader->ID, "model");
    glUniformMatrix4fv (modelLoc, 1, GL_FALSE, glm::value_ptr (model));
}
