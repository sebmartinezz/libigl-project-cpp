#off MODEL LOADER SANITY
add_executable(io-model-loader-off-sanity
    io-model-loader-off-sanity.cpp
    ${CMAKE_SOURCE_DIR}/src/io/model-loader.cpp
    ${CMAKE_SOURCE_DIR}/src/render/camera.cpp
    ${CMAKE_SOURCE_DIR}/src/render/mesh.cpp
    ${CMAKE_SOURCE_DIR}/src/render/shader.cpp
    ${CMAKE_SOURCE_DIR}/src/render/renderer.cpp
    ${CMAKE_SOURCE_DIR}/src/core/glfw-window.cpp
)
target_link_libraries(io-model-loader-off-sanity PRIVATE
    glfw
    glad
    OpenGL::GL
    Eigen3::Eigen
)

target_compile_definitions(io-model-loader-off-sanity PRIVATE ##adds model sirectory
    DATA_DIR="${DATA_DIR}"
    OFF_MODEL_DIR="${OFF_MODEL_DIR}"
)

target_include_directories(io-model-loader-off-sanity PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    /opt/libigl/include
)


#obj model loader sanity
add_executable(io-model-loader-obj-sanity
    io-model-loader-obj-sanity.cpp
    ${CMAKE_SOURCE_DIR}/src/io/model-loader.cpp
    ${CMAKE_SOURCE_DIR}/src/render/camera.cpp
    ${CMAKE_SOURCE_DIR}/src/render/mesh.cpp
    ${CMAKE_SOURCE_DIR}/src/render/shader.cpp
    ${CMAKE_SOURCE_DIR}/src/render/renderer.cpp
    ${CMAKE_SOURCE_DIR}/src/core/glfw-window.cpp
)
target_link_libraries(io-model-loader-obj-sanity PRIVATE
    glfw
    glad
    OpenGL::GL
    Eigen3::Eigen
)

target_compile_definitions(io-model-loader-obj-sanity PRIVATE ##adds model sirectory
    DATA_DIR="${DATA_DIR}"
    OFF_MODEL_DIR="${OFF_MODEL_DIR}"
    OBJ_MODEL_DIR="${OBJ_MODEL_DIR}"
)

target_include_directories(io-model-loader-obj-sanity PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    /opt/libigl/include
)

