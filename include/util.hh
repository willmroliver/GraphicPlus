#ifndef INCLUDE_UTIL_HH
#define INCLUDE_UTIL_HH

#include <string>
#include <fstream>

inline std::string file_to_cstr(std::string path) {
    std::ifstream file { path };
    std::istreambuf_iterator<char> begin { file }, end;
    return { begin, end };
}

#endif