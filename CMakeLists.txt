cmake_minimum_required(VERSION 3.14)

project(libiglproject CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenGL REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_check_modules(GLFW REQUIRED glfw3)

find_package(Eigen3 REQUIRED)
find_package(glfw3 REQUIRED)


# trae glad
include(FetchContent)
FetchContent_Declare(
  glad
  GIT_REPOSITORY https://github.com/Dav1dde/glad.git
  GIT_TAG v0.1.36
)
FetchContent_MakeAvailable(glad)

set(MODEL_DIR "${CMAKE_SOURCE_DIR}/data") #para que encuentren las mallass


#informacion de sanity en general, luego de traer glad
add_executable(sanity-info sanity/test-container/sanity-info.cpp)

target_link_libraries(sanity-info PRIVATE
    glfw
    glad
    Eigen3::Eigen
    GL
)

function(add_opengl_example NAME SOURCE) #añadir ejemplos de opengl
    add_executable(${NAME} ${SOURCE})
    target_include_directories(${NAME} PRIVATE ${GLFW_INCLUDE_DIRS})
    target_link_libraries(${NAME} PRIVATE ${OPENGL_LIBRARIES} ${GLFW_LIBRARIES})
endfunction()

function(add_libigl_example NAME SOURCE) #añadir ejemplos de libigl
    add_executable(${NAME} ${SOURCE})
    target_compile_definitions(${NAME} PRIVATE MODEL_DIR="${MODEL_DIR}")
    target_include_directories(${NAME} PRIVATE /opt/libigl/include)
    target_link_libraries(${NAME} PRIVATE Eigen3::Eigen glfw glad GL)
endfunction()

add_subdirectory(sanity/test-opengl/triangle)
add_subdirectory(sanity/test-opengl/rubik)
add_subdirectory(sanity/test-libigl/camelhead)
add_subdirectory(sanity/test-libigl/rotating-cow)