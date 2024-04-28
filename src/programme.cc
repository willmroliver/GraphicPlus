#include "programme.hh"
#include "util.hh"
#include <iostream>
#include <vector>

Programme::Programme(std::string vertex_path, std::string fragment_path):
    vertex_path { vertex_path }, 
    fragment_path { fragment_path } 
{
    const auto [success, info_log] = Programme::create_shader(vertex_id, GL_VERTEX_SHADER, vertex_path);
    if (!success) {
        exit(1);
    }

    const auto [success2, info_log2] = Programme::create_shader(fragment_id, GL_FRAGMENT_SHADER, fragment_path);
    if (!success2) {
        exit(1);
    }

    const auto [success3, info_log3] = Programme::create_programme(programme_id, { vertex_id, fragment_id });
    if (!success3) {
        exit(1);
    }
}

Programme::~Programme() {
    Programme::delete_shader(vertex_id);
    Programme::delete_shader(fragment_id);
    Programme::delete_programme(programme_id);
}

Programme::operator GLuint() {
    return programme_id;
}

std::pair<int, std::string> Programme::create_shader(unsigned int& id, int type, std::string path) {
    std::string src = file_to_cstr(path);
    const char* cstr = src.c_str();

    id = glCreateShader(type);
    glShaderSource(id, 1, &cstr, NULL);
    glCompileShader(id);

    int success;
    char info_log[512];

    glGetShaderiv(id, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(id, 512, NULL, info_log);
    }

    return { success, info_log };
}

std::pair<int, std::string> Programme::create_programme(unsigned int& id, std::vector<unsigned int> shaders) {
    id = glCreateProgram();

    for (auto shader : shaders) {
        glAttachShader(id, shader);
    }
    
    glLinkProgram(id);

    int success;
    char info_log[512];

    glGetProgramiv(id, GL_LINK_STATUS, &success);

    if (!success) {
        glGetProgramInfoLog(id, 512, NULL, info_log);
    }

    for (auto shader : shaders) {
        glDeleteShader(shader);
    }

    return { success, info_log };
}

void Programme::delete_shader(unsigned int& id) {
    glDeleteShader(id);
    id = 0;
}

void Programme::delete_programme(unsigned int& id) {
    glDeleteProgram(id);
    id = 0;
}