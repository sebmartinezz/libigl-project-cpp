
#bunny example
add_executable(curvature-bunny-example
    curvature-bunny-example.cpp
    ${CMAKE_SOURCE_DIR}/src/geometry/curvature.cpp
    ${CMAKE_SOURCE_DIR}/src/render/camera.cpp
    ${CMAKE_SOURCE_DIR}/src/render/mesh.cpp
    ${CMAKE_SOURCE_DIR}/src/render/shader.cpp
    ${CMAKE_SOURCE_DIR}/src/render/renderer.cpp
    ${CMAKE_SOURCE_DIR}/src/core/glfw-window.cpp
    ${CMAKE_SOURCE_DIR}/src/io/model-loader.cpp
)

target_include_directories(curvature-bunny-example PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    /opt/libigl/include
)

target_link_libraries(curvature-bunny-example PRIVATE
    glfw
    glad
    OpenGL::GL
    Eigen3::Eigen
)

target_compile_definitions(curvature-bunny-example PRIVATE
    DATA_DIR="${DATA_DIR}"
    OFF_MODEL_DIR="${OFF_MODEL_DIR}"
    OBJ_MODEL_DIR="${OBJ_MODEL_DIR}"
)

#cow example
add_executable(curvature-cow-example
    curvature-cow-example.cpp
    ${CMAKE_SOURCE_DIR}/src/geometry/curvature.cpp
    ${CMAKE_SOURCE_DIR}/src/render/camera.cpp
    ${CMAKE_SOURCE_DIR}/src/render/mesh.cpp
    ${CMAKE_SOURCE_DIR}/src/render/shader.cpp
    ${CMAKE_SOURCE_DIR}/src/render/renderer.cpp
    ${CMAKE_SOURCE_DIR}/src/core/glfw-window.cpp
    ${CMAKE_SOURCE_DIR}/src/io/model-loader.cpp
)

target_include_directories(curvature-cow-example PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    /opt/libigl/include
)

target_link_libraries(curvature-cow-example PRIVATE
    glfw
    glad
    OpenGL::GL
    Eigen3::Eigen
)

target_compile_definitions(curvature-cow-example PRIVATE
    DATA_DIR="${DATA_DIR}"
    OFF_MODEL_DIR="${OFF_MODEL_DIR}"
    OBJ_MODEL_DIR="${OBJ_MODEL_DIR}"
)

#screwdriver example
add_executable(curvature-screwdriver-example
    curvature-screwdriver-example.cpp
    ${CMAKE_SOURCE_DIR}/src/geometry/curvature.cpp
    ${CMAKE_SOURCE_DIR}/src/render/camera.cpp
    ${CMAKE_SOURCE_DIR}/src/render/mesh.cpp
    ${CMAKE_SOURCE_DIR}/src/render/shader.cpp
    ${CMAKE_SOURCE_DIR}/src/render/renderer.cpp
    ${CMAKE_SOURCE_DIR}/src/core/glfw-window.cpp
    ${CMAKE_SOURCE_DIR}/src/io/model-loader.cpp
)

target_include_directories(curvature-screwdriver-example PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    /opt/libigl/include
)

target_link_libraries(curvature-screwdriver-example PRIVATE
    glfw
    glad
    OpenGL::GL
    Eigen3::Eigen
)

target_compile_definitions(curvature-screwdriver-example PRIVATE
    DATA_DIR="${DATA_DIR}"
    OFF_MODEL_DIR="${OFF_MODEL_DIR}"
    OBJ_MODEL_DIR="${OBJ_MODEL_DIR}"
)

#planexy example
add_executable(curvature-planexy-example
    curvature-planexy-example.cpp
    ${CMAKE_SOURCE_DIR}/src/geometry/curvature.cpp
    ${CMAKE_SOURCE_DIR}/src/render/camera.cpp
    ${CMAKE_SOURCE_DIR}/src/render/mesh.cpp
    ${CMAKE_SOURCE_DIR}/src/render/shader.cpp
    ${CMAKE_SOURCE_DIR}/src/render/renderer.cpp
    ${CMAKE_SOURCE_DIR}/src/core/glfw-window.cpp
    ${CMAKE_SOURCE_DIR}/src/io/model-loader.cpp
)

target_include_directories(curvature-planexy-example PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    /opt/libigl/include
)

target_link_libraries(curvature-planexy-example PRIVATE
    glfw
    glad
    OpenGL::GL
    Eigen3::Eigen
)

target_compile_definitions(curvature-planexy-example PRIVATE
    DATA_DIR="${DATA_DIR}"
    OFF_MODEL_DIR="${OFF_MODEL_DIR}"
    OBJ_MODEL_DIR="${OBJ_MODEL_DIR}"
)

#cheburashka example
add_executable(curvature-cheburashka-example
    curvature-cheburashka-example.cpp
    ${CMAKE_SOURCE_DIR}/src/geometry/curvature.cpp
    ${CMAKE_SOURCE_DIR}/src/render/camera.cpp
    ${CMAKE_SOURCE_DIR}/src/render/mesh.cpp
    ${CMAKE_SOURCE_DIR}/src/render/shader.cpp
    ${CMAKE_SOURCE_DIR}/src/render/renderer.cpp
    ${CMAKE_SOURCE_DIR}/src/core/glfw-window.cpp
    ${CMAKE_SOURCE_DIR}/src/io/model-loader.cpp
)

target_include_directories(curvature-cheburashka-example PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    /opt/libigl/include
)

target_link_libraries(curvature-cheburashka-example PRIVATE
    glfw
    glad
    OpenGL::GL
    Eigen3::Eigen
)

target_compile_definitions(curvature-cheburashka-example PRIVATE
    DATA_DIR="${DATA_DIR}"
    OFF_MODEL_DIR="${OFF_MODEL_DIR}"
    OBJ_MODEL_DIR="${OBJ_MODEL_DIR}"
)

#armadillo example
add_executable(curvature-armadillo-example
    curvature-armadillo-example.cpp
    ${CMAKE_SOURCE_DIR}/src/geometry/curvature.cpp
    ${CMAKE_SOURCE_DIR}/src/render/camera.cpp
    ${CMAKE_SOURCE_DIR}/src/render/mesh.cpp
    ${CMAKE_SOURCE_DIR}/src/render/shader.cpp
    ${CMAKE_SOURCE_DIR}/src/render/renderer.cpp
    ${CMAKE_SOURCE_DIR}/src/core/glfw-window.cpp
    ${CMAKE_SOURCE_DIR}/src/io/model-loader.cpp
)

target_include_directories(curvature-armadillo-example PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    /opt/libigl/include
)

target_link_libraries(curvature-armadillo-example PRIVATE
    glfw
    glad
    OpenGL::GL
    Eigen3::Eigen
)

target_compile_definitions(curvature-armadillo-example PRIVATE
    DATA_DIR="${DATA_DIR}"
    OFF_MODEL_DIR="${OFF_MODEL_DIR}"
    OBJ_MODEL_DIR="${OBJ_MODEL_DIR}"
)