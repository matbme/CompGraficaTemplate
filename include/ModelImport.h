#ifndef MODELIMPORT_H
#define MODELIMPORT_H

#include <memory>

#include "Mesh.h"

namespace ModelImporter {
std::unique_ptr<Mesh> fromObj (std::string path);
}

#endif
