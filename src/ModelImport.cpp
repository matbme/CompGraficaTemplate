#include "ModelImport.h"

// Simple hashing function to compare instructions at O(n)
constexpr unsigned int hash(const char* str, int h = 0) {
    return !str[h] ? 5381 : (hash(str, h+1)*33) ^ str[h];
}

std::unique_ptr<Model> ModelImporter::Obj::import (std::string const &path) {
    auto ret_model = std::make_unique<Model> ();
    bool new_mesh = false;

    // We store file values in temp vectors until we are done importing everything
    std::vector<glm::vec3> temp_vertex_pos;
    std::vector<glm::vec3> temp_vertex_norm;
    std::vector<glm::vec2> temp_vertex_tex;

    std::ifstream file (path);
    std::string line;
    while (std::getline (file, line)) {
        if (line == "\r") continue; // Ignore carriage returns
        if (line[0] == '#') continue; // Ignore comments

        if (new_mesh) {
            ret_model->meshes.push_back (Mesh ());
            new_mesh = false;
        }

        auto tokens = ModelImporter::tokenize_line (line);
        switch (hash (tokens[0].c_str ())) {
            case hash ("mtllib"):
                std::cout << "Is mtllib" << std::endl;
                break;
            case hash ("o"):
                std::cout << "Is o" << std::endl;
                break;
            case hash ("v"): // Vertex position
                temp_vertex_pos.push_back (
                        glm::vec3 (std::strtof (tokens[1].c_str (), NULL), 
                                   std::strtof (tokens[2].c_str (), NULL), 
                                   std::strtof (tokens[3].c_str (), NULL)));
                break;
            case hash ("vt"): // Vertex texture coords
                temp_vertex_tex.push_back (
                        glm::vec2 (std::strtof (tokens[1].c_str (), NULL), 
                                   std::strtof (tokens[2].c_str (), NULL)));
                break;
            case hash ("vn"): // Vertex normals
                temp_vertex_norm.push_back (
                        glm::vec3 (std::strtof (tokens[1].c_str (), NULL), 
                                   std::strtof (tokens[2].c_str (), NULL), 
                                   std::strtof (tokens[3].c_str (), NULL)));
                break;
            case hash ("g"): // New group
                new_mesh = true;
                break;
            case hash ("usemtl"):
                std::cout << "Is usemtl" << std::endl;
                break;
            case hash ("s"):
                std::cout << "Is s" << std::endl;
                break;
            case hash ("f"): // Face
                for (int i = 1 ; i <= 3 ; i++) {
                    auto [model_ptr, pos] = ModelImporter::Obj::_add_vertex (
                            tokens[i], 
                            std::move (ret_model), 
                            &temp_vertex_pos, 
                            &temp_vertex_norm, 
                            &temp_vertex_tex);
                    ret_model.swap (model_ptr);
                    ret_model->meshes.back().indices.push_back (pos);
                }
                break;
            default:
                std::cout << "Something else" << std::endl;
        }
    }

    ret_model->setup_meshes ();

    return ret_model;
}

inline std::array<int, 3> ModelImporter::Obj::_tokenize_face_param (std::string face_param) {
    std::array<int, 3> ret;
    std::string bld;
    int it = 0;

    for (const auto character : face_param+"/") {
        if (character != '/') bld += character;
        else {
            ret[it] = std::atoi (bld.c_str ());
            bld.clear ();
            it++;
        }
    }

    return ret;
}

inline std::pair<std::unique_ptr<Model> ,unsigned int> ModelImporter::Obj::_add_vertex (
    std::string vertex_param,
    std::unique_ptr<Model> ret_model,
    std::vector<glm::vec3> const *temp_vertex_pos,
    std::vector<glm::vec3> const *temp_vertex_norm,
    std::vector<glm::vec2> const *temp_vertex_tex)
{
    auto tokenized_param = ModelImporter::Obj::_tokenize_face_param(vertex_param);
    Vertex constructed = {
        temp_vertex_pos->at (tokenized_param[0] - 1),
        temp_vertex_norm->at (tokenized_param[2] - 1),
        tokenized_param[1] ? temp_vertex_tex->at (tokenized_param[1] - 1) : glm::vec2()
    };

    // Checks whether constructed vertex already exists
    auto result = std::find (ret_model->meshes.back().vertices.begin (),
                             ret_model->meshes.back().vertices.end (),
                             constructed);

    // Append to vertex vector if it doesn't exist, otherwire returns its position
    int pos = -1;
    if (result == ret_model->meshes.back().vertices.end ()) {
        ret_model->meshes.back().vertices.push_back (constructed);
        pos = ret_model->meshes.back().vertices.size() - 1;
    } else {
        pos = std::distance(ret_model->meshes.back().vertices.begin (), result);
    }

    assert (pos != -1);
    return std::pair<std::unique_ptr<Model>, unsigned int> (std::move (ret_model), pos);
}


inline std::vector<std::string> ModelImporter::tokenize_line(std::string line) {
    std::vector<std::string> tokens;
    std::istringstream iss (line);
    std::copy (std::istream_iterator<std::string>(iss),
               std::istream_iterator<std::string>(),
               std::back_inserter(tokens));

    return tokens;
}
