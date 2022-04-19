#include "ModelImport.h"

// Simple hashing function to compare instructions at O(n)
constexpr unsigned int hash(const char* str, int h = 0) {
    return !str[h] ? 5381 : (hash(str, h+1)*33) ^ str[h];
}

std::unique_ptr<Model> ModelImporter::fromObj (std::string const &path) {
    std::unique_ptr<Model> ret_model = std::make_unique<Model>();

    std::ifstream file (path);

    std::string line;
    while (std::getline (file, line)) {
        if (line[0] == '#') continue;

        std::vector<std::string> tokens;
        std::istringstream iss (line);
        std::copy (std::istream_iterator<std::string>(iss),
                   std::istream_iterator<std::string>(),
                   std::back_inserter(tokens));


        switch (hash (tokens[0].c_str ())) {
            case hash ("mtllib"):
                std::cout << "Is mtllib" << std::endl;
                break;
            case hash ("o"):
                std::cout << "Is o" << std::endl;
                break;
            case hash ("v"):
                ret_model->unique_vertex_pos.push_back (
                        std::make_shared<glm::vec3> (
                            glm::vec3 (std::strtof (tokens[1].c_str (), NULL), 
                                       std::strtof (tokens[2].c_str (), NULL), 
                                       std::strtof (tokens[3].c_str (), NULL))));
                break;
            case hash ("vt"):
                ret_model->unique_vertex_tex.push_back (
                        std::make_shared<glm::vec2> (
                            glm::vec2 (std::strtof (tokens[1].c_str (), NULL), 
                                       std::strtof (tokens[2].c_str (), NULL))));
                break;
            case hash ("vn"):
                ret_model->unique_vertex_norm.push_back (
                        std::make_shared<glm::vec3> (
                            glm::vec3 (std::strtof (tokens[1].c_str (), NULL), 
                                       std::strtof (tokens[2].c_str (), NULL), 
                                       std::strtof (tokens[3].c_str (), NULL))));
                break;
            case hash ("g"):
                ret_model->meshes.push_back (Mesh ());
                ret_model->unique_vertex_pos_offset += (ret_model->unique_vertex_pos.size () - ret_model->unique_vertex_pos_offset);
                ret_model->unique_vertex_tex_offset += (ret_model->unique_vertex_tex.size () - ret_model->unique_vertex_tex_offset);
                ret_model->unique_vertex_norm_offset += (ret_model->unique_vertex_norm.size () - ret_model->unique_vertex_norm_offset);
                break;
            case hash ("usemtl"):
                std::cout << "Is usemtl" << std::endl;
                break;
            case hash ("s"):
                std::cout << "Is s" << std::endl;
                break;
            case hash ("f"):
                ret_model->meshes.back ().vertices.push_back (Vertex ());
                break;
            default:
                std::cout << "Something else" << std::endl;
        }
    }
    return nullptr;
}

inline std::array<int, 3> ModelImporter::tokenize_face_param (std::string face_param) {
        std::vector<std::string> tokens;
        std::array<int, 3> ret;

        std::istringstream iss (face_param);
        std::copy (std::istream_iterator<std::string>(iss),
                   std::istream_iterator<std::string>(),
                   std::back_inserter(tokens));

        for (int i = 0 ; i < 3 ; i++) {
            ret[i] = std::stoi (tokens[i]);
        }

        return ret;
}
