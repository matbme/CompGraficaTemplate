#ifndef CUBE_H
#define CUBE_H

#include <GLFW/glfw3.h>

class Cube {
public:
    static constexpr GLfloat vertices[] = {
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

    static constexpr unsigned int indices[] = {
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

    static constexpr int size_vertices () {
        return sizeof (vertices);
    }
    
    static constexpr int size_indices () {
        return sizeof (indices);
    }
};

#endif
