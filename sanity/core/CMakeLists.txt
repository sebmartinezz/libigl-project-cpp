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

