
#CURVATURE SANITY
add_executable(geometry-curvature-sanity
    geometry-curvature-sanity.cpp
    ${CMAKE_SOURCE_DIR}/src/geometry/curvature.cpp
    ${CMAKE_SOURCE_DIR}/src/io/model-loader.cpp
    ${CMAKE_SOURCE_DIR}/src/render/mesh.cpp
)
target_link_libraries(geometry-curvature-sanity PRIVATE
    glfw
    glad
    OpenGL::GL
    Eigen3::Eigen
)

target_compile_definitions(geometry-curvature-sanity PRIVATE ##adds model sirectory
    DATA_DIR="${DATA_DIR}"
    OFF_MODEL_DIR="${OFF_MODEL_DIR}"
)

target_include_directories(geometry-curvature-sanity PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    /opt/libigl/include
)
#DEFORMATION SANITY
add_executable(geometry-deformation-sanity
    geometry-deformation-sanity.cpp
    ${CMAKE_SOURCE_DIR}/src/geometry/deformation.cpp
    ${CMAKE_SOURCE_DIR}/src/render/camera.cpp
    ${CMAKE_SOURCE_DIR}/src/render/mesh.cpp
    ${CMAKE_SOURCE_DIR}/src/render/shader.cpp
    ${CMAKE_SOURCE_DIR}/src/render/renderer.cpp
    ${CMAKE_SOURCE_DIR}/src/core/glfw-window.cpp)

target_link_libraries(geometry-deformation-sanity PRIVATE
    glfw
    glad
    OpenGL::GL
    Eigen3::Eigen
)

target_compile_definitions(geometry-deformation-sanity PRIVATE ##adds model sirectory
    DATA_DIR="${DATA_DIR}"
    OFF_MODEL_DIR="${OFF_MODEL_DIR}"
)

target_include_directories(geometry-deformation-sanity PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    /opt/libigl/include
)