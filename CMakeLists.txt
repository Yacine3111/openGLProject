cmake_minimum_required(VERSION 3.28)
project(openGLProject)

set(CMAKE_CXX_STANDARD 17)

set(GLFW_DIR ${CMAKE_SOURCE_DIR}/libraries)

add_executable(openGLProject main.cpp glad.c)

target_include_directories(openGLProject PRIVATE ${GLFW_DIR}/include)
target_link_directories(openGLProject PRIVATE ${GLFW_DIR}/lib)

target_link_libraries(openGLProject glfw3 opengl32)