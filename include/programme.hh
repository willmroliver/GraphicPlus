#ifndef INCLUDE_PROGRAMME_HH
#define INCLUDE_PROGRAMME_HH

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <string>
#include <iostream>

class Programme {
    private:
        std::string vertex_path;
        std::string fragment_path;
        unsigned int vertex_id;
        unsigned int fragment_id;
        unsigned int programme_id;

    public:
        Programme() = default;
        Programme(std::string vertex_path, std::string fragment_path);
        ~Programme();
        operator GLuint();

        static std::pair<int, std::string> create_shader(unsigned int& id, int type, std::string path);
        static std::pair<int, std::string> create_programme(unsigned int& id, std::vector<unsigned int> shaders);
        static void delete_shader(unsigned int& id);
        static void delete_programme(unsigned int& id);
};  

#endif