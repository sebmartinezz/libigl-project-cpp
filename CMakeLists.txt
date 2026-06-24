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

function(opengl_example NAME SOURCE)
    add_executable(${NAME} ${SOURCE})
    target_include_directories(${NAME} PRIVATE ${GLFW_INCLUDE_DIRS})
    target_link_libraries(${NAME} PRIVATE glfw glad OpenGL::GL)
endfunction()

function(libigl_example NAME SOURCE)
    add_executable(${NAME} ${SOURCE})
    target_compile_definitions(${NAME} PRIVATE MODEL_DIR="${MODEL_DIR}")
    target_include_directories(${NAME} PRIVATE
        ${CMAKE_SOURCE_DIR}/include
        /opt/libigl/include
    )
    target_link_libraries(${NAME} PRIVATE glfw glad Eigen3::Eigen OpenGL::GL)
endfunction()

add_subdirectory(sanity)
add_subdirectory(demos)