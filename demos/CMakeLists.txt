
#BUNNY DEMO FOR COLORING CURVATURE
add_executable(bunny-demo
    bunny-demo.cpp
    ${CMAKE_SOURCE_DIR}/src/geometry/geometry.cpp
    ${CMAKE_SOURCE_DIR}/src/render/mesh.cpp
    ${CMAKE_SOURCE_DIR}/src/render/shader.cpp
    ${CMAKE_SOURCE_DIR}/src/render/renderer.cpp
    ${CMAKE_SOURCE_DIR}/src/core/glfw-window.cpp
    ${CMAKE_SOURCE_DIR}/src/io/model-loader.cpp
)

target_include_directories(bunny-demo PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    /opt/libigl/include
)

target_link_libraries(bunny-demo PRIVATE
    glfw
    glad
    OpenGL::GL
    Eigen3::Eigen
)

target_compile_definitions(bunny-demo PRIVATE
    DATA_DIR="${DATA_DIR}"
    OFF_MODEL_DIR="${OFF_MODEL_DIR}"
    OBJ_MODEL_DIR="${OBJ_MODEL_DIR}"
)