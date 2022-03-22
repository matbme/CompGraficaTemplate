#ifndef SHAPE_H
#define SHAPE_H

#include <GLFW/glfw3.h>

class Shape {
public:
    Shape (const GLfloat *vertices, const unsigned int *indices, int size_vertices, int size_indices) {
        this->vertices = vertices;
        this->indices = indices;

        this->size_vertices = size_vertices;
        this->size_indices = size_indices;
    }

    const GLfloat *vertices;
    const unsigned int *indices;

    // TODO: This gets assigned for each new Object, needs to be a pointer back to declaration
    int size_vertices, size_indices;
};

#endif
