cmake_minimum_required(VERSION 3.10)
project(OpenGLTriangle CXX)

set(CMAKE_CXX_STANDARD 23)

#usar g++14
set(CMAKE_C_COMPILER gcc-14)
set(CMAKE_CXX_COMPILER g++-14)

#buscar las librerias en el container
find_package(OpenGL REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_check_modules(GLFW REQUIRED glfw3)

#crear ejecutable
add_executable(triangle triangle-example.cpp)

#enlazar librerias al ejecutable
target_include_directories(triangle PRIVATE ${GLFW_INCLUDE_DIRS})
target_link_libraries(triangle PRIVATE ${OPENGL_LIBRARIES} ${GLFW_LIBRARIES})