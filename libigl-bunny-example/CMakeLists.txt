cmake_minimum_required(VERSION 3.14)

project(bunnyExample CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 1. Buscar Eigen y GLFW nativos del contenedor (Instalados al instante por apt)
find_package(Eigen3 REQUIRED)
find_package(glfw3 REQUIRED)
find_package(Threads REQUIRED)

# 2. Descargar SOLO GLAD (Tarda 2 segundos, pesa nada)
include(FetchContent)
FetchContent_Declare(
  glad
  GIT_REPOSITORY https://github.com/Dav1dde/glad.git
  GIT_TAG        v0.1.36
)
FetchContent_MakeAvailable(glad)

# 3. Definir tu ejecutable
add_executable(bunny bunny-example.cpp)

# 4. Pasar la ruta de los headers de libigl
target_include_directories(bunny PRIVATE "/opt/libigl/include")

# 5. Enlazar todo de forma limpia
target_link_libraries(bunny PRIVATE 
    Eigen3::Eigen
    glfw
    glad           # El target de FetchContent
    Threads::Threads
    GL
)