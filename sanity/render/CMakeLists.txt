
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

#CAMERA SANITY
add_executable(render-camera-sanity
    render-camera-sanity.cpp
    ${CMAKE_SOURCE_DIR}/src/render/camera.cpp
    ${CMAKE_SOURCE_DIR}/src/render/mesh.cpp
    ${CMAKE_SOURCE_DIR}/src/render/shader.cpp
    ${CMAKE_SOURCE_DIR}/src/render/renderer.cpp
    ${CMAKE_SOURCE_DIR}/src/core/glfw-window.cpp
)


target_link_libraries(render-camera-sanity PRIVATE
    glfw
    glad
    OpenGL::GL
    Eigen3::Eigen
)


target_compile_definitions(render-camera-sanity PRIVATE
    DATA_DIR="${DATA_DIR}"
    OFF_MODEL_DIR="${OFF_MODEL_DIR}"
)


target_include_directories(render-camera-sanity PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    /opt/libigl/include
)
