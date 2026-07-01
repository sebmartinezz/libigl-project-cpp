# Engine Architecture

## Architecture Overview

The project is organized as a modular real-time mesh visualization system built from `OpenGL`, `GLFW`, `GLAD`, `Eigen`, `GLM`, and `libigl`.  
All modules are defined through the header files in `include/` and implemented in the source files inside `src/`. Each one is responsible for a specific part of the rendering and geometry processing pipeline:

- `core/`: Handles window creation, OpenGL context initialization, input handling, and the main application loop.
- `render/`: Contains the rendering pipeline components, including shaders, GPU buffer management, mesh rendering, and camera systems.
- `io/`: Provides mesh loading functionality, handling the conversion from external model files (`.obj`, `.off`) into the internal mesh representation.
- `geometry/`: Contains geometry processing operations, including curvature computation and mesh deformation algorithms.

The general workflow of the system is:
```text
Model file (.obj / .off) (from model repository)
-> Model loader
-> Mesh representation (CPU side)
-> Geometry processing (curvature / deformation)
-> Update mesh data
-> GPU buffer upload (VAO, VBO, EBO)
-> Rendering pipeline
-> Final OpenGL visualization
```

## Modules Breakdown

### Core Module

#### `glfw-window`

Encapsulates window creation using `GLFW`, initializes the OpenGL context, loads OpenGL function pointers via `GLAD`, and manages the basic application loop and input/event handling.

This module serves as the interface between the operating system and the rendering engine. During initialization, this module creates the internal `Window` object and the corresponding GLFW window resource, configures the OpenGL context, and loads OpenGL function pointers through `GLAD` to load the OpenGL function pointers provided by the graphics driver.

In addition to context creation, it provides utility functions for common window operations such as event polling, buffer swapping, mouse position retrieval, mouse button state queries, and window destruction. By centralizing all GLFW-related functionality, the rest of the engine can interact with the window system through a small and consistent API without directly depending on GLFW calls.

The module is also responsible for establishing the OpenGL execution environment before any rendering resources, such as shaders or meshes, are created.

### Render Module

#### `renderer`

Provides basic rendering operations, including OpenGL viewport configuration and framebuffer clearing.

This module acts as an abstraction over common OpenGL state operations required during rendering. It assumes that an OpenGL context has already been created by the window system and provides functions to initialize the renderer, configure the viewport, and prepare the framebuffer for each frame.

During initialization, it enables **depth testing**, allowing OpenGL to correctly handle visibility between overlapping 3D surfaces by comparing fragment depth values instead of relying only on draw order.

The renderer also manages frame preparation operations. The viewport configuration defines the region of the window where OpenGL renders and the clear operation resets both the color and depth buffers before drawing a new frame.

The typical rendering sequence is:

```text
renderer_init()
-> renderer_set_viewport()
-> renderer_clear()
-> draw scene objects
-> swap buffers
```

#### `shader`

Manages shader creation and usage, including loading vertex and fragment shader files, compiling shader programs, and passing data to shaders.

The module builds a shader object by loading GLSL source code from external files, sending the code to OpenGL for compilation and linking the compiled vertex and fragment shaders into a single GPU program. The resulting OpenGL program is stored as an `unsigned int` identifier used to reference the shader object during rendering.

The compilation process is performed by OpenGL, which converts the GLSL source code into instructions that can be executed by the GPU. After linking both shader stages, the individual shader objects are deleted because they are no longer needed.

The module also provides an interface for sending data from the CPU to the GPU through shader uniforms. It supports common uniform types such as integers, floats, and transformation matrices using `GLM`.

The general shader pipeline is:

```text
GLSL files
-> Load source code
-> Compile vertex shader + fragment shader
-> Link shader program
-> Activate program with glUseProgram()
-> Send uniforms to GPU
```

#### `mesh`

Manages GPU representation of a 3D mesh as an object, including OpenGL buffers (VAO, VBO, EBO) and vertex attribute setup. It stores geometry on the CPU using `Eigen` (positions, colors, indices), uploads it in an interleaved format, and supports dynamic updates of vertex positions and colors.

In the CPU mesh representation, operations such as deformation and curvature visualization from other modules can modify vertex data before updating the GPU buffers. During the upload process, the module converts the mesh object's `Eigen::MatrixXf` data into an interleaved `std::vector<float>` vertex buffer. Each vertex stores both position and color attributes, resulting in the following buffer:

```text
[x0, y0, z0, r0, g0, b0, x1, y1, z1, r1, g1, b1, ...]
```
This data is uploaded into a Vertex Buffer Object (VBO), while the mesh connectivity information is stored in an Element Buffer Object (EBO). The Vertex Array Object (VAO) stores the configuration of the vertex attributes (position and color), allowing OpenGL to correctly interpret the buffer data during rendering.

The mesh upload pipeline is:

```text
Eigen mesh data
-> Interleaved vertex buffer (position + color)
-> VBO + EBO creation
-> VAO attribute configuration
-> GPU-ready mesh
```
The module also supports dynamic updates without recreating the whole mesh. Vertex positions and colors can be modified directly on the CPU representation and updated on the GPU using buffer sub-data operations. This allows geometry deformation and curvature-based color changes.

The rendering process is handled through indexed drawing:

```text
Mesh::draw()
-> Bind VAO (created before)
-> glDrawElements()
-> Render triangles
```

#### `camera`

Implements an orbit (spherical) camera system around a fixed target. It maintains view and projection matrices using `GLM`, and supports mouse-driven orbital rotation via yaw/pitch angles. The camera position is computed from spherical coordinates.

The camera position is obtained by converting spherical coordinates into Cartesian coordinates:

```text
yaw + pitch + distance
-> spherical coordinates
-> Cartesian position (x,y,z)
-> view matrix
```

The view matrix is generated using `glm::lookAt`, which transforms world coordinates into camera space based on the camera position, target point, and up direction. The projection matrix is generated using a perspective projection, converting the 3D scene into the final screen representation.

The camera pipeline is:
```text
Camera position
-> View matrix + Projection matrix
-> Shader transformation
-> Rendered image
```

### Input/Output Module

#### `model-loader`

The model loader converts external mesh files (`.off` / `.obj`) into the internal data structure used by the engine. It uses `libigl` file readers to extract vertex positions and face indices, then transforms this information into the `Mesh` representation based on `Eigen` matrices.

The loading process is independent from the rendering system. The loader only handles reading and converting geometry data, while the `Mesh` module is responsible for preparing the data for GPU rendering.

The model loading pipeline is:

```text
Mesh file (.obj / .off)
->libigl reader
-> Vertex positions (V), Face indices (F)
-> Mesh object
-> Rendering / Geometry modules
```

The loader also initializes **default vertex colors** after loading. Since models usually only contain geometry information, the mesh starts with a default **white** color buffer that can later be modified by geometry processing modules such as curvature.

### Geometry Module
#### `curvature`

Computes per-vertex curvature from an existing `Mesh` using `libigl`, extracting its geometry directly from the mesh’s Eigen-based representation. It calculates Gaussian curvature values and stores them as a scalar field associated with each vertex.

The computed curvature values are then transformed into vertex colors using a `tanh scaling` function. This normalization reduces the influence of *extreme* curvature values and maps the scalar curvature field into a range suitable for visualization. The resulting colors are stored directly in the mesh color buffer of the `mesh`, allowing the rendering pipeline to display curvature variations on the surface.

The curvature processing pipeline is:
```text
Mesh geometry
-> Extract vertices and faces
-> libigl Gaussian curvature
-> Scalar curvature per vertex
-> tanh normalization
-> Color mapping
-> Mesh vertex colors
```

The color map represents increasing curvature values:  
`Purple (lower curvature) -> Blue -> Green -> Yellow -> Orange -> Red (higher curvature)`  
This module only modifies geometric attributes of the mesh and does **not** interact directly with OpenGL. The updated colors are later uploaded by the `Mesh` module and displayed by the rendering pipeline.

#### `deformation`

Provides geometric deformation operations on a `Mesh` by directly modifying its vertex positions, producing dynamic shape changes that update the mesh.

It applies geometric transformations directly to the mesh vertex positions stored in the CPU `Eigen` representation. Instead of creating a new mesh, the existing vertex data is modified in place, allowing the changes to be continuously visualized after updating the GPU buffers.

The deformation pipeline is:
```text
Original mesh positions
-> Compute deformation parameters
-> Modify vertex positions
-> Update GPU buffer
-> Render updated mesh
```
The deformation uses the original vertex positions as the source geometry, preventing accumulated transformations when the operation is applied repeatedly. This allows the mesh to be animated or modified dynamically while maintaining a stable reference state.

This module only handles geometric changes and remains independent from the rendering system. After the vertex positions are modified, the `Mesh` module is responsible for synchronizing the updated data with the GPU for visualization.
