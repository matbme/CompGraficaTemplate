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

    std::vector<std::shared_ptr<glm::vec3>> unique_vertex_pos;
    std::vector<std::shared_ptr<glm::vec3>> unique_vertex_norm;
    std::vector<std::shared_ptr<glm::vec2>> unique_vertex_tex;

    unsigned int unique_vertex_pos_offset = 0;
    unsigned int unique_vertex_norm_offset = 0;
    unsigned int unique_vertex_tex_offset = 0;
};

#endif
