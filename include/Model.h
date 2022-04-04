#ifndef MODEL_H
#define MODEL_H

#include <string>
#include <vector>

#include "Mesh.h"

class Model {
public:
    Model (std::string path);
    void draw (Shader &shader);
private:
    std::vector<Mesh> meshes;
    std::string directory;
};

#endif
