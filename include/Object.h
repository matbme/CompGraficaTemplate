#ifndef OBJECT_H
#define OBJECT_H

#include "Shader.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Object {
public:
    Object ();
    ~Object ();

    // Set Atributos
    void setTexture (int texID);
    void setShader (Shader *shader);

    // Get Atributos
    unsigned int getTexID ();
    Shader *getShader ();
    glm::vec3 getPosition ();
    glm::vec3 getDimension ();
    float getAngle ();

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
    void draw ();
    void update ();

protected:
    GLuint VAO; // ID buffer de geometria 
    glm::mat4 model; // Matrix de transformacao
    
    unsigned int texID; // ID da textura
    Shader *shader; // ponteiro para objeto de shader

    // Atributos visuais do objeto
    glm::vec3 pos, scale;
    float angle;
};

#endif
