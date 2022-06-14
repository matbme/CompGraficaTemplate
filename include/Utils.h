#ifndef UTILS_H
#define UTILS_H

#include <iterator>
#include <sstream>
#include <string>
#include <vector>

namespace Utils {
std::vector<std::string> tokenize_line (std::string line);
std::string join_tokens (std::vector<std::string> tokens, int start_offset);

// Simple hashing function to compare instructions at O(n)
constexpr unsigned int hash (const char* str, int h = 0) {
    return !str[h] ? 5381 : (hash(str, h+1)*33) ^ str[h];
}

}

#endif
