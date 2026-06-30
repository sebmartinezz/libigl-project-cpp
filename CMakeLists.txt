cmake_minimum_required(VERSION 3.16)

project(libiglproject CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(Eigen3 REQUIRED)

# trae glad
include(FetchContent)

FetchContent_Declare(
  glad
  GIT_REPOSITORY https://github.com/Dav1dde/glad.git
  GIT_TAG v0.1.36
)

FetchContent_MakeAvailable(glad)
get_target_property(GLAD_INCLUDE_DIR glad INTERFACE_INCLUDE_DIRECTORIES)

include_directories(
    ${CMAKE_SOURCE_DIR}/include
    ${glad_SOURCE_DIR}/include
) #añadir esos path
set(DATA_DIR "${CMAKE_SOURCE_DIR}/data")
set(OBJ_MODEL_DIR "${CMAKE_SOURCE_DIR}/data/_obj-models") #para los modelos obj
set(OFF_MODEL_DIR "${CMAKE_SOURCE_DIR}/data/_off-models") #para los modelos off

#[
add_subdirectory(sanity/core)
add_subdirectory(sanity/render)
add_subdirectory(sanity/io)
add_subdirectory(sanity/geometry)

function(curvature_example NAME MAIN)
    add_executable(${NAME}
        ${MAIN}

        ${CMAKE_SOURCE_DIR}/src/geometry/curvature.cpp

        ${CMAKE_SOURCE_DIR}/src/render/camera.cpp
        ${CMAKE_SOURCE_DIR}/src/render/mesh.cpp
        ${CMAKE_SOURCE_DIR}/src/render/shader.cpp
        ${CMAKE_SOURCE_DIR}/src/render/renderer.cpp

        ${CMAKE_SOURCE_DIR}/src/core/glfw-window.cpp

        ${CMAKE_SOURCE_DIR}/src/io/model-loader.cpp
    )


    target_include_directories(${NAME} PRIVATE
        ${CMAKE_SOURCE_DIR}/include
        /opt/libigl/include
    )


    target_link_libraries(${NAME} PRIVATE
        glfw
        glad
        OpenGL::GL
        Eigen3::Eigen
    )


    target_compile_definitions(${NAME} PRIVATE
        DATA_DIR="${DATA_DIR}"
        OFF_MODEL_DIR="${OFF_MODEL_DIR}"
        OBJ_MODEL_DIR="${OBJ_MODEL_DIR}"
    )
endfunction()

add_subdirectory(examples/curvature)
#add_subdirectory(examples/deformation)
#add_subdirectory(examples/both)