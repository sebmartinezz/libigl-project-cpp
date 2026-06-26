
#BUNNY DEMO FOR COLORING CURVATURE
add_executable(curvature-bunny-demo
    curvature-bunny-demo.cpp
    ${CMAKE_SOURCE_DIR}/src/geometry/curvature.cpp
    ${CMAKE_SOURCE_DIR}/src/render/camera.cpp
    ${CMAKE_SOURCE_DIR}/src/render/mesh.cpp
    ${CMAKE_SOURCE_DIR}/src/render/shader.cpp
    ${CMAKE_SOURCE_DIR}/src/render/renderer.cpp
    ${CMAKE_SOURCE_DIR}/src/core/glfw-window.cpp
    ${CMAKE_SOURCE_DIR}/src/io/model-loader.cpp
)

target_include_directories(curvature-bunny-demo PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    /opt/libigl/include
)

target_link_libraries(curvature-bunny-demo PRIVATE
    glfw
    glad
    OpenGL::GL
    Eigen3::Eigen
)

target_compile_definitions(curvature-bunny-demo PRIVATE
    DATA_DIR="${DATA_DIR}"
    OFF_MODEL_DIR="${OFF_MODEL_DIR}"
    OBJ_MODEL_DIR="${OBJ_MODEL_DIR}"
)

#COW DEMO FOR COLORING CURVATURE
add_executable(curvature-cow-demo
    curvature-cow-demo.cpp
    ${CMAKE_SOURCE_DIR}/src/geometry/curvature.cpp
    ${CMAKE_SOURCE_DIR}/src/render/camera.cpp
    ${CMAKE_SOURCE_DIR}/src/render/mesh.cpp
    ${CMAKE_SOURCE_DIR}/src/render/shader.cpp
    ${CMAKE_SOURCE_DIR}/src/render/renderer.cpp
    ${CMAKE_SOURCE_DIR}/src/core/glfw-window.cpp
    ${CMAKE_SOURCE_DIR}/src/io/model-loader.cpp
)

target_include_directories(curvature-cow-demo PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    /opt/libigl/include
)

target_link_libraries(curvature-cow-demo PRIVATE
    glfw
    glad
    OpenGL::GL
    Eigen3::Eigen
)

target_compile_definitions(curvature-cow-demo PRIVATE
    DATA_DIR="${DATA_DIR}"
    OFF_MODEL_DIR="${OFF_MODEL_DIR}"
    OBJ_MODEL_DIR="${OBJ_MODEL_DIR}"
)

#SCREWDRIVER DEMO FOR COLORING CURVATURE
add_executable(curvature-screwdriver-demo
    curvature-screwdriver-demo.cpp
    ${CMAKE_SOURCE_DIR}/src/geometry/curvature.cpp
    ${CMAKE_SOURCE_DIR}/src/render/camera.cpp
    ${CMAKE_SOURCE_DIR}/src/render/mesh.cpp
    ${CMAKE_SOURCE_DIR}/src/render/shader.cpp
    ${CMAKE_SOURCE_DIR}/src/render/renderer.cpp
    ${CMAKE_SOURCE_DIR}/src/core/glfw-window.cpp
    ${CMAKE_SOURCE_DIR}/src/io/model-loader.cpp
)

target_include_directories(curvature-screwdriver-demo PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    /opt/libigl/include
)

target_link_libraries(curvature-screwdriver-demo PRIVATE
    glfw
    glad
    OpenGL::GL
    Eigen3::Eigen
)

target_compile_definitions(curvature-screwdriver-demo PRIVATE
    DATA_DIR="${DATA_DIR}"
    OFF_MODEL_DIR="${OFF_MODEL_DIR}"
    OBJ_MODEL_DIR="${OBJ_MODEL_DIR}"
)