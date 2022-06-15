#ifndef CURVES_H
#define CURVES_H

#include <GLFW/glfw3.h>

#include <glm/fwd.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>

class BSpline {
public:
    BSpline ();
    ~BSpline () {};

    void genCurve (int resolution);
    void draw ();
    void addPoint (glm::vec3 p) { points.push_back(p); }
private:
    std::vector<glm::vec3> points;
    std::vector<glm::vec3> curve;
    glm::mat4 M;
    GLuint VAO, VBO, cVBO;
};

#endif
