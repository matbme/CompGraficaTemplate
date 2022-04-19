#ifndef MODELIMPORT_H
#define MODELIMPORT_H

#include <iostream>
#include <iterator>
#include <memory>
#include <string>
#include <utility>
#include <vector>
#include <array>

#include "Model.h"

namespace ModelImporter {
std::unique_ptr<Model> fromObj (std::string const &path);

inline std::array<int, 3> tokenize_face_param (std::string face_param);
}

#endif
