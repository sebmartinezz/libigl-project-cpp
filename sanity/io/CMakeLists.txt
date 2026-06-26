#MODEL LOADER SANITY
add_executable(io-model-loader-sanity
    io-model-loader-sanity.cpp
    ${CMAKE_SOURCE_DIR}/src/io/model-loader.cpp
    ${CMAKE_SOURCE_DIR}/src/render/camera.cpp
    ${CMAKE_SOURCE_DIR}/src/render/mesh.cpp
    ${CMAKE_SOURCE_DIR}/src/render/shader.cpp
    ${CMAKE_SOURCE_DIR}/src/render/renderer.cpp
    ${CMAKE_SOURCE_DIR}/src/core/glfw-window.cpp
)
target_link_libraries(io-model-loader-sanity PRIVATE
    glfw
    glad
    OpenGL::GL
    Eigen3::Eigen
)

target_compile_definitions(io-model-loader-sanity PRIVATE ##adds model sirectory
    DATA_DIR="${DATA_DIR}"
    OFF_MODEL_DIR="${OFF_MODEL_DIR}"
)

target_include_directories(io-model-loader-sanity PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    /opt/libigl/include
)
