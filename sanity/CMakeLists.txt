

# CORE WINDOW SANITY
add_executable(core-window-sanity
    core-window-sanity.cpp
    ${CMAKE_SOURCE_DIR}/src/core/glfw-window.cpp
)

target_link_libraries(core-window-sanity PRIVATE
    glfw
    glad
    OpenGL::GL
)


# RENDERER SANITY
add_executable(render-renderer-sanity
    render-renderer-sanity.cpp
    ${CMAKE_SOURCE_DIR}/src/render/renderer.cpp
    ${CMAKE_SOURCE_DIR}/src/core/glfw-window.cpp #renderer también usa window
)

target_link_libraries(render-renderer-sanity PRIVATE
    glfw
    glad
    OpenGL::GL
)


# BACKEND SANITY
add_executable(backend-sanity
    backend-sanity.cpp
)

target_link_libraries(backend-sanity PRIVATE
    glfw
    glad
    OpenGL::GL
    Eigen3::Eigen
)

#SHADER SANITY
add_executable(render-shader-sanity
    render-shader-sanity.cpp
    ${CMAKE_SOURCE_DIR}/src/render/shader.cpp
    ${CMAKE_SOURCE_DIR}/src/render/renderer.cpp
    ${CMAKE_SOURCE_DIR}/src/core/glfw-window.cpp
)
target_link_libraries(render-shader-sanity PRIVATE
    glfw
    glad
    OpenGL::GL
    Eigen3::Eigen
)

target_compile_definitions(render-shader-sanity PRIVATE ##adds model sirectory
    DATA_DIR="${DATA_DIR}"
)

#MESH SANITY
add_executable(render-mesh-sanity
    render-mesh-sanity.cpp
    ${CMAKE_SOURCE_DIR}/src/render/mesh.cpp
    ${CMAKE_SOURCE_DIR}/src/render/shader.cpp
    ${CMAKE_SOURCE_DIR}/src/render/renderer.cpp
    ${CMAKE_SOURCE_DIR}/src/core/glfw-window.cpp
)
target_link_libraries(render-mesh-sanity PRIVATE
    glfw
    glad
    OpenGL::GL
    Eigen3::Eigen
)

target_compile_definitions(render-mesh-sanity PRIVATE ##adds model sirectory
    DATA_DIR="${DATA_DIR}"
)

#MODEL LOADER SANITY
add_executable(io-model-loader-sanity
    io-model-loader-sanity.cpp
    ${CMAKE_SOURCE_DIR}/src/io/model-loader.cpp
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

#GEOMETRY SANITY
add_executable(geometry-geometry-sanity
    geometry-geometry-sanity.cpp
    ${CMAKE_SOURCE_DIR}/src/geometry/geometry.cpp
    ${CMAKE_SOURCE_DIR}/src/io/model-loader.cpp
    ${CMAKE_SOURCE_DIR}/src/render/mesh.cpp
)
target_link_libraries(geometry-geometry-sanity PRIVATE
    glfw
    glad
    OpenGL::GL
    Eigen3::Eigen
)

target_compile_definitions(geometry-geometry-sanity PRIVATE ##adds model sirectory
    DATA_DIR="${DATA_DIR}"
    OFF_MODEL_DIR="${OFF_MODEL_DIR}"
)

target_include_directories(geometry-geometry-sanity PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    /opt/libigl/include
)
