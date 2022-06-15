#include "Level.h"
#include "Curves.h"
#include "Light.h"
#include "Utils.h"

using namespace Utils;

template<>
Object *Level::_add_element_to_scene<Object>(Element &element, const std::unique_ptr<Scene>& scene) {
    element.params.push_back({"shader", scene->get_shader ()});
    auto constructed_object = std::make_unique<Object> (element.params);
    scene.get ()->add_object (constructed_object);
    return scene.get ()->get_last_object ();
}

template<>
DirectionalLight *Level::_add_element_to_scene<DirectionalLight>(Element &element, const std::unique_ptr<Scene>& scene) {
    auto constructed_dirlight = std::make_unique<DirectionalLight> (element.params);
    scene.get ()->add_dirLight (constructed_dirlight);
    return scene.get ()->get_dirLight ();
}

template<>
PointLight *Level::_add_element_to_scene<PointLight>(Element &element, const std::unique_ptr<Scene>& scene) {
    auto constructed_pointLight = std::make_unique<PointLight> (element.params);
    scene.get ()->add_pointLight (constructed_pointLight);
    return scene.get ()->get_last_pointLight ();
}

std::unique_ptr<Scene> Level::load_scene_from_level(std::string level_path) {
    std::unique_ptr<Scene> ret_scene;

    std::map<std::string, std::string> scene_params;
    std::map<std::string, Element> scene_elements;
    Element *def_block = nullptr;

    ElementType add_block_type;
    std::any add_block = nullptr;

    std::ifstream file (level_path);
    std::string line;
    while (std::getline (file, line)) {
        if (line == "\r") continue; // Ignore carriage returns
        if (line == "") continue; // Ignore empty lines
        if (line[0] == '#') continue; // Ignore comments

        auto tokens = tokenize_line (line);
        switch (hash (tokens[0].c_str ())) {
            case hash ("set"): { // Scene param
                scene_params[tokens[1]] = join_tokens(tokens, 2);
                break;
            }
            case hash ("init_scene"): { // Scene initializer
                assert (ret_scene == nullptr); // Make sure we only call it once

                auto shader_paths = tokenize_line (scene_params["shaders"]);
                ret_scene = std::make_unique<Scene> (
                    std::atoi (scene_params["window_width"].c_str ()),
                    std::atoi (scene_params["window_height"].c_str ()),
                    scene_params["window_name"],
                    shader_paths[0].substr (1, shader_paths[0].size () - 2),
                    shader_paths[1].substr (1, shader_paths[0].size () - 2)
                );
                break;
            }
            case hash ("def"): { // Scene element
                scene_elements[tokens[1]] = Element {
                    .type = ElementType (hash (tokens[3].c_str ())),
                    .params = {}
                };
                if (scene_elements[tokens[1]].type == BEZIER) {
                    Curves::Bezier::create_new(tokens[1]);
                }
                if (tokens.back () == "{") def_block = &scene_elements[tokens[1]];
                break;
            }
            case hash ("add"): { // Add element to scene
                assert (ret_scene != nullptr);
                switch (scene_elements[tokens[1]].type) {
                    case OBJ: {
                        auto ret = Level::_add_element_to_scene<Object> (scene_elements[tokens[1]], ret_scene);
                        if (tokens.back () == "{") add_block = ret;
                        add_block_type = scene_elements[tokens[1]].type;
                        break;
                    }
                    case DIRLIGHT: {
                        auto ret = Level::_add_element_to_scene<DirectionalLight> (scene_elements[tokens[1]], ret_scene);
                        if (tokens.back () == "{") add_block = ret;
                        add_block_type = scene_elements[tokens[1]].type;
                        break;
                    }
                    case POINTLIGHT: {
                        auto ret = Level::_add_element_to_scene<PointLight> (scene_elements[tokens[1]], ret_scene);
                        if (tokens.back () == "{") add_block = ret;
                        add_block_type = scene_elements[tokens[1]].type;
                        break;
                    }
                    default: break;
                }
                break;
            }
            case hash ("}"): { // End block
                assert((def_block != nullptr) || (add_block.has_value())); // Check whether it is closing something
                if (def_block != nullptr) def_block = nullptr;
                else add_block = nullptr;
                break;
            }
            default: {
                if (def_block != nullptr) { // def block param
                    if (def_block->type == BEZIER) {
                        Curves::Bezier::instanced[Curves::Bezier::last_added]->addPoint (glm::vec3 (
                            std::strtof (tokens[1].c_str (), NULL),
                            std::strtof (tokens[2].c_str (), NULL),
                            std::strtof (tokens[3].c_str (), NULL)
                        ));
                    } else {
                        if (tokens.size() == 2)
                            def_block->params.push_back ({tokens[0], tokens[1]});
                        else
                            def_block->params.push_back ({tokens[0], std::move(tokens)});
                    }
                } else if (add_block.has_value()) { // add block instruction
                    switch (add_block_type) {
                        case OBJ: {
                            Level::_set_parameter_for_element<Object> (
                                    *std::any_cast<Object*> (add_block),
                                    tokens[0],
                                    tokens.begin ());
                            break;
                        }
                        case DIRLIGHT: {
                            Level::_set_parameter_for_element<DirectionalLight> (
                                    *std::any_cast<DirectionalLight*> (add_block),
                                    tokens[0],
                                    tokens.begin ());
                            break;
                        }
                        case POINTLIGHT: {
                            Level::_set_parameter_for_element<PointLight> (
                                    *std::any_cast<PointLight*> (add_block),
                                    tokens[0],
                                    tokens.begin ());
                            break;
                        }
                        default: break;
                    }
                } else { // Invalid token
                    std::cout << "Unprocessed token: " << tokens[0] << std::endl;
                }
            }
        }
    }

    return std::move (ret_scene);
}

template<typename T>
void Level::_set_parameter_for_element (T& element, std::string param, std::vector<std::string>::iterator args) {
    element.apply (&element, param, args);
}
