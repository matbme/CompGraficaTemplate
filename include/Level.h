#ifndef LEVEL_H
#define LEVEL_H

#include "Scene.h"
#include "Utils.h"

#include <variant>

namespace Level {
enum ElementType : int {
    OBJ   = Utils::hash ("Object"),
    DIRLIGHT = Utils::hash ("DirectionalLight"),
    POINTLIGHT = Utils::hash ("PointLight")
};

struct Element {
    ElementType type;
    std::vector<std::pair<std::string, std::any>> params;
};

std::unique_ptr<Scene> load_scene_from_level (std::string level_path);

template<typename T>
T *_add_element_to_scene (Element& element, const std::unique_ptr<Scene>& scene);

template<typename T>
void _set_parameter_for_element (T& element, std::string param, std::vector<std::string>::iterator args);
}

#endif
