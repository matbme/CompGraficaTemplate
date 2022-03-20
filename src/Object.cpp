#include "Object.h"

Object::Object () {
GLfloat vertices[] = {
//       x     y     z     r    g    b

        // base
        -0.5, -0.5, -0.5, 1.0, 1.0, 0.0, // A - 0
        -0.5, -0.5,  0.5, 0.0, 1.0, 1.0, // B - 1
         0.5, -0.5, -0.5, 1.0, 0.0, 1.0, // C - 2
         0.5, -0.5,  0.5, 1.0, 0.0, 1.0, // D - 3

        // topo
        -0.5,  0.5, -0.5, 1.0, 1.0, 0.0, // E - 4
        -0.5,  0.5,  0.5, 0.0, 1.0, 1.0, // F - 5
         0.5,  0.5, -0.5, 1.0, 0.0, 1.0, // G - 6
         0.5,  0.5,  0.5, 1.0, 0.0, 1.0, // H - 7
	};
    unsigned int indices[] = {
        // base
        0, 1, 2,
        1, 2, 3,
        // topo
        4, 5, 6,
        5, 6, 7,
        // faces
        1, 3, 5,
        3, 5, 7,
        0, 1, 4,
        1, 4, 5,
        0, 2, 4,
        2, 4, 6,
        2, 3, 6,
        3, 6, 7,
    };

	unsigned int VBO, EBO;
    glGenVertexArrays (1, &VAO);
    glGenBuffers (1, &VBO);
    glGenBuffers (1, &EBO);

    glBindVertexArray (VAO);

    glBindBuffer (GL_ARRAY_BUFFER, VBO);
    glBufferData (GL_ARRAY_BUFFER, sizeof (vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData (GL_ELEMENT_ARRAY_BUFFER, sizeof (indices), indices, GL_STATIC_DRAW);

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

void Object::setTexture (int texID) { this->texID = texID; }

void Object::setShader (Shader* shader) {
    this->shader = shader;
    shader->Use ();
}

void Object::draw () {
	glBindVertexArray (VAO);
	glDrawElements (GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	glBindVertexArray (0);
}

void Object::update () {
	GLint modelLoc = glGetUniformLocation (shader->ID, "model");
	glUniformMatrix4fv (modelLoc, 1, GL_FALSE, glm::value_ptr (model));
}
