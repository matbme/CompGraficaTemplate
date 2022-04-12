#ifndef MODELIMPORT_H
#define MODELIMPORT_H

#include <iostream>
#include <iterator>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "Model.h"

namespace ModelImporter {
std::unique_ptr<Model> fromObj (std::string const &path);
}

#endif
