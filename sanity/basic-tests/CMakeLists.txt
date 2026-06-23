

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
    MODEL_DIR="${MODEL_DIR}"
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
    MODEL_DIR="${MODEL_DIR}"
)