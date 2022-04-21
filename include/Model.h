#ifndef MODEL_H
#define MODEL_H

#include <string>
#include <vector>

#include "Mesh.h"

class Model {
public:
    Model ();
    void draw (Shader &shader);
    std::vector<Mesh> meshes;
};

#endif
