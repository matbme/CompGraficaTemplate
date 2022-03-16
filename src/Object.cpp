#include "Object.h"

Object::Object () {
    float vertices[] = {
        // positions          // colors           // texture coords

        // bottom
         0.5f,  0.5f, -0.5f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0, // top right
         0.5f, -0.5f, -0.5f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, -0.5f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
        -0.5f,  0.5f, -0.5f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f,  // top left 

        // top
         0.5f,  0.5f,  0.5f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0, // top right
         0.5f, -0.5f,  0.5f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
        -0.5f, -0.5f,  0.5f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
        -0.5f,  0.5f,  0.5f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f,  // top left 
    };
    unsigned int indices[] = {
        // bottom
        0, 1, 3, // first triangle
        1, 2, 3, // second triangle

        // top
        4, 5, 7, // first triangle
        5, 6, 7, // second triangle
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
    glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof (float), (void*) 0);
    glEnableVertexAttribArray (0);
    // color attribute
    glVertexAttribPointer (1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof (float), (void*) (3 * sizeof (float)));
    glEnableVertexAttribArray (1);
    // texture coord attribute
    glVertexAttribPointer (2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof (float), (void*) (6 * sizeof (float)));
    glEnableVertexAttribArray (2);

    transform = glm::mat4 (1); //matriz identidade
    texID = -1; //ainda não temos
    shader = NULL; //ainda não temos
    pos = glm::vec3 (0.0f, 0.0f, 0.0f);
    scale = glm::vec3 (1.0f, 1.0f, 1.0f);
    angle = 0.0f;
}

void Object::setTexture (int texID)
{
	this->texID = texID;
}

void Object::setRotation (float angle, glm::vec3 axis, bool reset)
{
	if (reset) transform = glm::mat4 (1);
	transform = glm::rotate (transform, angle, axis);
}

void Object::setTranslation (glm::vec3 displacements, bool reset)
{
	if (reset) transform = glm::mat4 (1);
	transform = glm::translate (transform, displacements);
}

void Object::setScale (glm::vec3 scaleFactors, bool reset)
{
	if (reset) transform = glm::mat4 (1);
	transform = glm::scale (transform, scaleFactors);
	scale = scaleFactors;
}

void Object::draw()
{
	glBindTexture (GL_TEXTURE_2D, texID);
	glUniform1i (glGetUniformLocation (shader->ID, "ourTexture1"), 0);

	glBindVertexArray (VAO);
	glDrawElements (GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray (0);
}

void Object::update()
{
	setTranslation (pos);
	setRotation (angle, glm::vec3 (0.0f, 0.0f, 1.0f), false);
	setScale (scale, false);

	GLint transformLoc = glGetUniformLocation (shader->ID, "model");
	glUniformMatrix4fv (transformLoc, 1, GL_FALSE, glm::value_ptr (transform));
}
