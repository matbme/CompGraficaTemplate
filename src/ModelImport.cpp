#include "ModelImport.h"

// Simple hashing function to compare instructions at O(n)
constexpr unsigned int hash(const char* str, int h = 0) {
    return !str[h] ? 5381 : (hash(str, h+1)*33) ^ str[h];
}

std::unique_ptr<Model> ModelImporter::fromObj (std::string const &path) {
    std::ifstream file (path);

    std::string line;
    while (std::getline (file, line)) {
        if (line[0] == '#') continue;

        std::vector<std::string> tokens;
        std::istringstream iss (line);
        std::copy (std::istream_iterator<std::string>(iss),
                   std::istream_iterator<std::string>(),
                   std::back_inserter(tokens));

        // for (auto tok : tokens) std::cout << tok << std::endl;

        switch (hash (tokens[0].c_str ())) {
            case hash ("mtllib"):
                std::cout << "Is mtllib" << std::endl;
                break;
            case hash ("o"):
                std::cout << "Is o" << std::endl;
                break;
            case hash ("v"):
                std::cout << "Is v" << std::endl;
                break;
            case hash ("vt"):
                std::cout << "Is vt" << std::endl;
                break;
            case hash ("vn"):
                std::cout << "Is vn" << std::endl;
                break;
            case hash ("g"):
                std::cout << "Is g" << std::endl;
                break;
            case hash ("usemtl"):
                std::cout << "Is usemtl" << std::endl;
                break;
            case hash ("s"):
                std::cout << "Is s" << std::endl;
                break;
            case hash ("f"):
                std::cout << "Is f" << std::endl;
                break;
            default:
                std::cout << "Something else" << std::endl;
        }

        // return nullptr;
    }
    return nullptr;
}
