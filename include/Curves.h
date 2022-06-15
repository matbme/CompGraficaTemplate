#ifndef CURVES_H
#define CURVES_H

#include <GLFW/glfw3.h>

#include <glm/fwd.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <map>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

namespace Curves {
class BSpline {
public:
    BSpline (std::string name);
    ~BSpline ();

    static void create_new (std::string name);

    void genCurve (int resolution);
    void addPoint (glm::vec3 p) { points.push_back(p); }

    void print_curves () {
        int it = 0;
        for (auto point : this->curve)
            std::cout << ++it << ": " <<
            "X: " << point.x << "  " <<
            "Y: " << point.y << "  " <<
            "Z: " << point.z << std::endl;
    }

    static std::map<std::string, std::shared_ptr<Curves::BSpline>> instanced;
    static std::string last_added;

    std::vector<glm::vec3> curve;
private:
    std::string name;
    std::vector<glm::vec3> points;
    glm::mat4 M;
};

}

#endif
