#include "Curves.h"
#include "Utils.h"

using namespace Curves;

Bezier::Bezier (std::string name) {
    this->name = name;

    float scalar = 1.0 / 6.0;
    M = glm::mat4x4 (-1,  3, -3,  1,
                      3, -6,  3,  0,
                     -3,  3,  0,  0,
                      1,  0,  0,  0);
    M= M * scalar;

    Bezier::last_added = name;
}

void Bezier::create_new (std::string name) {
    Bezier::instanced[name] = std::make_shared<Bezier> (name);
}

Bezier::~Bezier () {
    Bezier::instanced.erase(this->name);
}

void Bezier::genCurve (int resolution) {
    float step = 1.0 / (float) resolution;
    float t = 0;

    for (int i = 0 ; i < points.size () - 3 ; i += 3) {
        for (float t = 0.0 ; t <= 1.0 ; t += step) {
            glm::vec3 p;
            glm::vec4 T (t*t*t, t*t, t, 1);
            glm::mat4x3 G (points[i].x, points[i].y, points[i].z,
                           points[i + 1].x, points[i + 1].y, points[i + 1].z,
                           points[i + 2].x, points[i + 2].y, points[i + 2].z,
                           points[i + 2].x, points[i + 3].y, points[i + 3].z);

            p = G * M * T;
            curve.push_back (p);
        }
    }
}

std::map<std::string, std::shared_ptr<Curves::Bezier>> Bezier::instanced = {};
std::string Bezier::last_added = "";
