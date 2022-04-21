#ifndef MODELIMPORT_H
#define MODELIMPORT_H

#include <algorithm>
#include <iostream>
#include <iterator>
#include <memory>
#include <string>
#include <utility>
#include <vector>
#include <array>

#include "Model.h"

namespace ModelImporter {
namespace Obj {
std::unique_ptr<Model> fromObj (std::string const &path);
inline std::array<int, 3> tokenize_face_param (std::string face_param);
inline unsigned int add_vertex (std::string vertex_param,
                        Model *ret_model,
                        std::vector<glm::vec3> const *temp_vertex_pos,
                        std::vector<glm::vec3> const *temp_vertex_norm,
                        std::vector<glm::vec2> const *temp_vertex_tex);
}

inline std::vector<std::string> tokenize_line (std::string line);
}

#endif
