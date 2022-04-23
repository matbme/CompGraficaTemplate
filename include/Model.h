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

    std::vector<Mesh> meshes;
};

#endif
