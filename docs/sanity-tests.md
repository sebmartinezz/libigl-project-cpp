
# Sanity Tests

## Running Tests

Each test is designed to check that a specific module can be initialized and used independently before integrating it with the rest of the engine. Run the tests after building the project following the instructions provided in [README.md](../README.md):

```bash
./build/sanity/<module>/<test>
```

For example:

```bash
./build/sanity/render/render-mesh-sanity
./build/sanity/geometry/geometry-deformation-sanity
```


## Expected Tests Behavior
### <span style="color:#9b59b6">Core Tests</span>
#### `backend-sanity`
Verifies that the basic project environment and required dependencies are working correctly.

Expected result:
- GLFW initializes successfully.
- A hidden test window is created successfully.
- The OpenGL context is created correctly.
- GLAD loads OpenGL function pointers successfully.
- The OpenGL version, renderer, and vendor information are printed.

Expected output:

```text
----backend sanity----
GLFW OK
GLAD OK
opengl version: <OpenGL version>
renderer: <GPU renderer>
vendor: <GPU vendor>

----end backend sanity----
```

#### `core-window-sanity`
Verifies GLFW initialization, OpenGL context creation, and GLAD loading.


Expected result:
- GLFW initializes successfully.
- An application window is created with the specified size and title.
- The OpenGL context is created correctly.
- The window remains open until it is manually closed.
- The event loop processes window events correctly.
- The window is destroyed successfully when the program exits.

Expected output:

```text
----window sanity----
OpenGL: <OpenGL version>
GLSL: <GLSL version>
window created

----end window sanity----
```
### <span style="color:#3498db">Render Tests</span>
#### `render-renderer-sanity`
Verifies the basic renderer initialization and OpenGL state configuration.


Expected result:
- A window is created successfully.
- The renderer initializes correctly.
- The OpenGL viewport is configured with the provided dimensions.
- The framebuffer is cleared every frame using the specified clear color.
- The window remains open until manually closed.

Expected output:

```text
----renderer sanity----
OpenGL: <OpenGL version>
GLSL: <GLSL version>
window created
renderer initialized
viewport OK

----end renderer sanity----
```
#### `render-shader-sanity`
Verifies shader loading, compilation, linking, and activation.

Expected result:
- A window is created successfully.
- The renderer initializes correctly.
- Vertex and fragment shader files are loaded.
- The shaders compile and link successfully.
- The shader program can be activated.
- A triangle is rendered using the created shader program.

Expected output:

```text
----shader sanity----
OpenGL: <OpenGL version>
GLSL: <GLSL version>
window created
shader ok

----end shader sanity----
```


#### `render-mesh-sanity`

Verifies the mesh module, including CPU-side mesh data management, GPU buffer creation, VAO/VBO/EBO configuration, vertex attribute setup, and mesh rendering.

Expected result:
- A window is created successfully.
- The shader program loads and activates correctly.
- Mesh vertex positions, colors, and indices are initialized correctly.
- The mesh data is uploaded to the GPU.
- VAO, VBO, and EBO are created and configured successfully.
- The mesh can be drawn using indexed rendering.

Expected output:

```text
----mesh sanity----
OpenGL: <OpenGL version>
GLSL: <GLSL version>
shader ok
setupgl called
mesh uploaded ok

----end mesh sanity----
```

#### `render-camera-sanity`
Verifies camera initialization and transformation matrix generation.

Expected result:
- A window is created successfully.
- The shader program loads and activates correctly.
- The camera initializes with the default target, orientation, and distance.
- View and projection matrices are generated correctly.
- Mouse input updates the camera orbit through yaw and pitch changes.
- The mesh is rendered using the camera transformation pipeline.

Expected output:

```text
---- camera sanity ----
OpenGL: <OpenGL version>
GLSL: <GLSL version>
shader ok
setupgl called
orbit: dx dy (when mouse click pressed)

---- end camera sanity ----
```

### <span style="color:#2ecc71">Input/Output Tests</span>
#### `io-model-loader-off/obj-sanity`
Verifies loading external mesh files and converting them into the internal `Mesh` representation.

Expected result:
- A window is created successfully.
- The shader program loads and activates correctly.
- The `.off`/`.obj` model file is loaded from disk using `libigl`.
- Vertex positions and face indices are converted into the internal `Mesh` representation.
- The mesh is uploaded to the GPU and rendered correctly.
- The loaded model can be viewed using the camera orbit controls.

Expected output:

```text
---- model loader (off/obj) sanity ----
OpenGL: <OpenGL version>
GLSL: <GLSL version>
model loaded in this path: <model path>
vertices: <number of vertices>
faces: <number of faces>
mesh loaded

---- end model loader (off/obj) sanity ----
```

### <span style="color:#e67e22">Geometry Tests</span>
#### `geometry-curvature-sanity`
Verifies curvature computation and curvature-based color mapping.

Expected result:
- The mesh file is loaded successfully.
- Gaussian curvature values are computed for each vertex using `libigl`.
- Curvature values are mapped into RGB colors.
- The resulting colors are stored in the mesh color buffer.

Expected output:

```text
---- curvature sanity ----
model loaded in this path: <model path>
vertices: <number of vertices>
faces: <number of faces>
mesh loaded
curvature computed
color mapping done
K[0] = <curvature value> | RGB = (<r>, <g>, <b>)
K[1] = <curvature value> | RGB = (<r>, <g>, <b>)
K[2] = <curvature value> | RGB = (<r>, <g>, <b>)
K[3] = <curvature value> | RGB = (<r>, <g>, <b>)
K[4] = <curvature value> | RGB = (<r>, <g>, <b>)
---- end curvature sanity ----
```

#### `geometry-deformation-sanity`
Verifies geometric deformation operations.

Expected result:
- A window is created successfully.
- The shader program loads and activates correctly.
- The mesh geometry is initialized correctly.
- The deformation function modifies vertex positions over time.
- Updated vertex positions are uploaded to the GPU.
- The deformed geometry is rendered continuously.

Expected output:

```text
---- deformation sanity ----
OpenGL: <OpenGL version>
GLSL: <GLSL version>
shader ok
setupgl called

---- end deformation sanity ----
```