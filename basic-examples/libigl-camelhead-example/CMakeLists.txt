cmake_minimum_required(VERSION 3.14)

project(CamelheadExample CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# find eigen and glfw
find_package(Eigen3 REQUIRED)
find_package(glfw3 REQUIRED)
find_package(Threads REQUIRED)

# download only glad
include(FetchContent)
FetchContent_Declare(
  glad
  GIT_REPOSITORY https://github.com/Dav1dde/glad.git
  GIT_TAG        v0.1.36
)
FetchContent_MakeAvailable(glad)

# ejecutable
add_executable(camelhead camelhead-example.cpp)

# libigl headers route
target_include_directories(camelhead PRIVATE "/opt/libigl/include")

# link
target_link_libraries(camelhead PRIVATE 
    Eigen3::Eigen
    glfw
    glad           # fetchcontent target
    Threads::Threads
    GL
)