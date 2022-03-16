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
    void setPosition (glm::vec3 pos);
    void setDimension (glm::vec3 scale);
    void setAngle (float angle);

    // Get Atributos
    unsigned int getTexID ();
    Shader *getShader ();
    glm::vec3 getPosition ();
    glm::vec3 getDimension ();
    float getAngle ();

    // Para controle direto da matriz de transformacoes
	void setRotation(float angle, glm::vec3 axis, bool reset = true);
	void setTranslation(glm::vec3 displacements, bool reset = true);
	void setScale(glm::vec3 scaleFactors, bool reset = true);

    // Gerenciamento
    void draw ();
    void update ();

protected:
    GLuint VAO; // ID buffer de geometria 
    glm::mat4 transform; // Matrix de transformacao
    
    unsigned int texID; // ID da textura
    Shader *shader; // ponteiro para objeto de shader

    // Atributos visuais do objeto
    glm::vec3 pos, scale;
    float angle;
};

#endif
