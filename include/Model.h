#ifndef MODEL_H
#define MODEL_H

#include <string>
#include <vector>

#include "Mesh.h"

class Model {
public:
    Model ();
    void draw ();
    void setup_meshes ();
    void set_shader (Shader *shader);

    void rotate (float angle, glm::vec3 axis, bool reset = false);
    void translate (glm::vec3 displacements, bool reset = false);
    void rescale (glm::vec3 scaleFactors, bool reset = false);

    void update ();

    std::vector<Mesh> meshes;
};

#endif
