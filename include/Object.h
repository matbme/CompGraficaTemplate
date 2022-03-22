#ifndef OBJECT_H
#define OBJECT_H

#include "Shader.h"
#include "Shape.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

template <class S>
class Object {
public:
    Object () {
        this->shape = new Shape (S::vertices, S::indices, S::size_vertices(), S::size_indices());

        unsigned int VBO, EBO;
        glGenVertexArrays (1, &VAO);
        glGenBuffers (1, &VBO);
        glGenBuffers (1, &EBO);

        glBindVertexArray (VAO);

        glBindBuffer (GL_ARRAY_BUFFER, VBO);
        glBufferData (GL_ARRAY_BUFFER, shape->size_vertices, shape->vertices, GL_STATIC_DRAW);

        glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData (GL_ELEMENT_ARRAY_BUFFER, shape->size_indices, shape->indices, GL_STATIC_DRAW);

        // position attribute
        glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof (float), (void*) 0);
        glEnableVertexAttribArray (0);
        // color attribute
        glVertexAttribPointer (1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof (float), (void*) (3 * sizeof (float)));
        glEnableVertexAttribArray (1);

        model = glm::mat4 (1); //matriz identidade
        // texID = -1; //ainda não temos
        shader = NULL; //ainda não temos
        pos = glm::vec3 (0.0f, 0.0f, 0.0f);
        scale = glm::vec3 (1.0f, 1.0f, 1.0f);
        angle = 0.0f;
    }
    ~Object () { }

    // Set Atributos
    void setTexture (int texID) {
        this->texID = texID;
    }
    void setShader (Shader *shader) {
        this->shader = shader;
        shader->Use ();
    }

    // Get Atributos
    unsigned int getTexID () { return this->texID; }
    Shader *getShader () { return this->shader; }
    glm::vec3 getPosition () { return this->pos; }
    glm::vec3 getScale () { return this->scale; }
    float getAngle () { return this->angle; }

    // Para controle direto da matriz de transformacoes
	inline void setRotation(float angle, glm::vec3 axis, bool reset = false) {
        if (reset) model = glm::mat4 (1);
        model = glm::rotate (model, angle, axis);
    }
	inline void setTranslation(glm::vec3 displacements, bool reset = false) {
        if (reset) model = glm::mat4 (1);
        model = glm::translate (model, displacements);
    }
	inline void setScale(glm::vec3 scaleFactors, bool reset = false) {
        if (reset) model = glm::mat4 (1);
        model = glm::scale (model, scaleFactors);
        scale = scaleFactors;
    }

    // Gerenciamento
    void draw () {
        glBindVertexArray (VAO);
        glDrawElements (GL_TRIANGLES, shape->size_indices / sizeof (unsigned int), GL_UNSIGNED_INT, 0);
        glBindVertexArray (0);
    }
    void update () {
        GLint modelLoc = glGetUniformLocation (shader->ID, "model");
        glUniformMatrix4fv (modelLoc, 1, GL_FALSE, glm::value_ptr (model));
    }

protected:
    GLuint VAO; // ID buffer de geometria 
    glm::mat4 model; // Matriz de transformacao
    
    unsigned int texID; // ID da textura
    Shader *shader; // ponteiro para objeto de shader

    // Atributos visuais do objeto
    glm::vec3 pos, scale;
    float angle;

    // Geometria e indices passados para a EBO
    Shape *shape;
};

#endif
