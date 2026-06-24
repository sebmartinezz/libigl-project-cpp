
#BUNNY DEMO FOR COLORING CURVATURE
add_executable(curvature-bunny-demo
    curvature-bunny-demo.cpp
    ${CMAKE_SOURCE_DIR}/src/geometry/curvature.cpp
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

##BUNNY DEMO FOR DEFORMATION IN CPU
#[[
add_executable(deformation-bunny-demo
    deformation-bunny-demo.cpp
    ${CMAKE_SOURCE_DIR}/src/geometry/deformation.cpp
    ${CMAKE_SOURCE_DIR}/src/geometry/curvature.cpp
    ${CMAKE_SOURCE_DIR}/src/render/mesh.cpp
    ${CMAKE_SOURCE_DIR}/src/render/shader.cpp
    ${CMAKE_SOURCE_DIR}/src/render/renderer.cpp
    ${CMAKE_SOURCE_DIR}/src/core/glfw-window.cpp
    ${CMAKE_SOURCE_DIR}/src/io/model-loader.cpp
)

target_include_directories(deformation-bunny-demo PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    /opt/libigl/include
)

target_link_libraries(deformation-bunny-demo PRIVATE
    glfw
    glad
    OpenGL::GL
    Eigen3::Eigen
)

target_compile_definitions(deformation-bunny-demo PRIVATE
    DATA_DIR="${DATA_DIR}"
    OFF_MODEL_DIR="${OFF_MODEL_DIR}"
    OBJ_MODEL_DIR="${OBJ_MODEL_DIR}"
)

]]