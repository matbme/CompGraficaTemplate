#include "Curves.h"

BSpline::BSpline () {
    float scalar = 1.0 / 6.0;
    M = glm::mat4x4 (-1,  3, -3,  1,
                      3, -6,  3,  0,
                     -3,  0,  3,  0,
                      1,  4,  1,  0);
    M= M * scalar;
}

void BSpline::genCurve (int resolution) {
    float step = 1.0 / (float) resolution;
    float t = 0;
    int control_points = this->points.size ();

    for (int i = 0 ; i < points.size () - 3 ; i += 3) {
        for (float t = 0.0 ; t <= 1.0 ; t += step) {
            glm::vec3 p;
            glm::vec4 T (t*t*t, t*t, t, 1);
            glm::mat4x3 G (points[i].x, points[i].y, points[i].z,
                           points[i + 1].x, points[i + 1].y, points[i + 1].z,
                           points[i + 2].x, points[i + 2].y, points[i + 2].z,
                           points[i + 3].x, points[i + 3].y, points[i + 3].z);

            p = G * M * T;
            curve.push_back (p);
        }
    }
}
