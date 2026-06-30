
# Dynamic Curvature Visualization of 3D Meshes Using Libigl and OpenGL

## About
This project presents a system for coloring three-dimensional models based on their curvature during continuous physical deformations, integrating a custom OpenGL-based mini graphics engine for the real-time loading, processing, deformation, and visualization of 3D models from the public libigl repository.  
Libigl is primarily used for geometric mesh processing and model loading, while the engine handles scene abstraction, graphics resource management, geometry updates during deformation and visualization, managing the communication between the CPU and the GPU through the rendering pipeline.

## Structure
The project is organized into modular components:

```
.
├── include/
│   ├── core/
│   │   └── glfw-window.h
│   │
│   ├── render/
│   │   ├── renderer.h
│   │   ├── shader.h
│   │   ├── mesh.h
│   │   └── camera.h
│   │
│   ├── io/
│   │   └── model-loader.h
│   │
│   └── geometry/
│       ├── curvature.h
│       └── deformation.h
│
├── src/
│
├── sanity/
│
├── examples/
│   ├── curvature/
│   ├── deformation/
│   └── both/
│
├── results/
│
└── utilities/
    ├── _obj-models/
    ├── _off-models/
    ├── vert-shader/
    └── frag-shader/
```

The `src/` and `sanity/` directories follow the same module organization defined in `include/`, with corresponding implementations and tests for each engine component.

### Modules Overview

- `include/`: Header files defining the engine modules.
- `src/`: Source files implementing the `.h` files in `include/`.
- `sanity/`: Tests for each module.
- `examples/`: Example applications demonstrating curvature visualization, mesh deformation, and their interaction.
- `results/`: Visualization results.
- `utilities/`: External resources, such as models and shader files.

### Implementation Overview

- **Core Components**
  - `glfw-window`: Encapsulates window creation using `GLFW`, initializes the OpenGL context, loads OpenGL function pointers via `GLAD`, and manages the basic application loop and input/event handling.

- **Rendering Components**
  - `renderer`: Provides basic rendering operations, including OpenGL viewport configuration and framebuffer clearing.
  - `shader`: Manages shader creation and usage, including loading vertex and fragment shader files, compiling shader programs, and passing data to shaders.
  - `mesh`: Manages GPU representation of a 3D mesh, including OpenGL buffers (VAO, VBO, EBO) and vertex attribute setup. It stores geometry on the CPU using `Eigen` (positions, colors, indices), uploads it in an interleaved format, and supports dynamic updates of vertex positions and colors.
  - `camera`: Implements an orbit (spherical) camera system around a fixed target. It maintains view and projection matrices using `GLM`, and supports mouse-driven orbital rotation via yaw/pitch angles. The camera position is computed from spherical coordinates.

- **IO Components**
  - `model-loader`: Loads mesh data from disk using `libigl`. Supports .off and .obj formats, converts the geometry into the engine’s internal `Mesh` representation, and handles basic error reporting and format validation.

- **Geometry Components**
  - `curvature`: Computes per-vertex curvature from an existing `Mesh` using `libigl`, extracting its geometry directly from the mesh’s Eigen-based representation. It maps scalar curvature values into vertex colors using *tanh scaling* and stores the result back into the mesh color buffer for visualization.
  - `deformation`: Provides geometric deformation operations on a `Mesh` by directly modifying its vertex positions, producing dynamic shape changes that update the mesh in place for real-time visualization.

## Requirements
- Docker
- OpenGL 4.x compatible graphics environment
- X server for graphical output
  - VcXsrv (Windows)
  - X11 (Linux)

## Docker Setup

### Building the Docker Image
Make sure Docker is running before building the image.  
From the project root directory:
```bash
docker build -t libiglproj .
```

This creates a Docker image named `libiglproj` containing all required dependencies and the project environment.

### Running the container (Windows PowerShell)
Make sure Docker and the X server are both running before launching the container.

First, get the IPv4 address for the X server using `ipconfig`, then run:

```powershell
docker run -it --rm -v "${PWD}:/workspace" -e DISPLAY=<IPv4>:0 libiglproj
```

`--rm` automatically removes the container when it exits. This prevents unused stopped containers from accumulating.

`-v "${PWD}:/workspace"` mounts the current host directory into the container:
  - *`${PWD}`* refers to the current directory on the host machine.
  - *`/workspace`* is the directory inside the container.

This allows files edited on the host machine to be directly available inside the container and vice versa.

`-e DISPLAY=<IPv4>:0` sets the DISPLAY environment variable inside the container, allowing graphical applications running inside Docker (such as OpenGL programs) to communicate with the host X server.

`<IPv4>` should be replaced with your actual IPv4 address, obtained before.  
:0 refers to the default display number.

### Running the container (Linux Terminal)
(TODO)

## Compilation and Execution
From the project root directory:
```bash
mkdir build
cmake --fresh -S . -B build && cmake --build build
```
`mkdir build` creates a separate directory for generated build files. **Run it only once**.  
`cmake --fresh -S . -B build` configures the project from the source directory (.) and generates the build system inside build.  
`cmake --build build` compiles the project using the generated configuration.

After building, executables can be found inside build/  
Run the executables with:
```bash
./build/<category>/<subdir>/<executable>
```
where `<category>` can be sanity or examples.

For example:
```bash
./build/sanity/render/render-camera-sanity
./build/examples/curvature/curvature-cow-example
```


## Sanity Tests

Run the sanity tests in the following order to verify that each module works correctly:
- **Core**
  - backend-sanity
  - core-window-sanity

- **Render**
  - render-renderer-sanity
  - render-shader-sanity
  - render-mesh-sanity
  - render-camera-sanity

- **IO**
  - io-model-loader-sanity

- **Geometry**
  - geometry-curvature-sanity
  - geometry-deformation-sanity

## Links

[GitHub - Repository](https://github.com/sebmartinezz/libigl-project-cpp)  
[Drive - Repository](https://drive.google.com/drive/folders/1ymkmy3yYDT-SRfTl61svm8XMh8n8oIXk?usp=sharing)  
[Models - Repository](https://github.com/libigl/libigl-tutorial-data.git)

## Additional Information

### Curvature Color Map
The color map represents increasing curvature values:  
`Purple (lower) → Blue → Green → Yellow → Orange → Red (higher)`

### Download models from the libigl tutorial dataset:
```bash
cd <model-directory>
curl -L -O https://raw.githubusercontent.com/libigl/libigl-tutorial-data/master/<model>.off
```
