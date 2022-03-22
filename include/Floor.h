#ifndef FLOOR_H
#define FLOOR_H

#include <GLFW/glfw3.h>

class Floor {
public:
    static constexpr GLfloat vertices[] = {
//       x     y     z     r    g    b
        // base
        -0.5, -0.5, -0.5, 1.0, 1.0, 0.0, // A - 0
        -0.5, -0.5,  0.5, 0.0, 1.0, 1.0, // B - 1
         0.5, -0.5, -0.5, 1.0, 0.0, 1.0, // C - 2
         0.5, -0.5,  0.5, 1.0, 0.0, 1.0, // D - 3
    };

    static constexpr unsigned int indices[] = {
        // base
        0, 1, 2,
        1, 2, 3,
    };

    static constexpr int size_vertices () {
        return sizeof (vertices);
    }
    
    static constexpr int size_indices () {
        return sizeof (indices);
    }
};

#endif
