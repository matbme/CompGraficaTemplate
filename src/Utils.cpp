#include "Utils.h"

std::vector<std::string> Utils::tokenize_line (std::string line) {
    std::vector<std::string> tokens;
    std::istringstream iss (line);
    std::copy (std::istream_iterator<std::string>(iss),
               std::istream_iterator<std::string>(),
               std::back_inserter(tokens));

    return tokens;
}

std::string Utils::join_tokens (std::vector<std::string> tokens, int start_offset = 0) {
    std::string joined_param = "";

    for (auto param = tokens.begin () + start_offset ; param != tokens.end () ; ++param) {
        joined_param += param->c_str();
        // Add space if not the last element
        if (param != tokens.end () - 1) joined_param += std::string (" ");
    }

    return joined_param;
}
