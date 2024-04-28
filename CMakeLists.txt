cmake_minimum_required(VERSION 3.26)
project(OpenGLPlayground VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED true)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic")

file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})

add_library(OpenGLPlayground "")
add_subdirectory(src)
target_include_directories(OpenGLPlayground PUBLIC include)

add_executable(ExecGL src/main.cc)
find_package(glfw3 3.3 REQUIRED)

target_link_libraries(OpenGLPlayground glfw)
target_link_libraries(ExecGL OpenGLPlayground)