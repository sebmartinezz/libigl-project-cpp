# Docker Setup

## Environment Description

This project uses Docker to provide a consistent development environment for building and running the codebase.  
The Docker environment contains all required dependencies, libraries, and tools needed by the project, including the C++ compiler, `CMake`, OpenGL-related packages, `GLFW`, `Eigen`, `GLM` and `libigl`.

Using Docker avoids manual installation and configuration of these dependencies on the host machine. The project can be compiled and executed inside the container while keeping the source files synchronized with the host system.  
The container will be configured to support graphical output through an X server, allowing OpenGL-based visualization to be displayed on the host machine while the project runs inside Docker.

## Docker Image

If you are in Windows, make sure Docker Desktop is running before building the image.

From the project root directory, run:

```bash
docker build -t libiglproj .
```

This creates a Docker image named `libiglproj` using the `Dockerfile` located in the current directory.  
The Docker image is based on Ubuntu 24.04 and configures the complete development environment, including:

- **C++ compiler setup**
  - Installs g++-14
  - Configures g++ and gcc to use version 14 by default
- **Build system**
  - cmake
  - make tools through build-essential
  - pkg-config
- **Graphics dependencies**
  - OpenGL development libraries
  - GLFW
  - GLU
  - Mesa utilities
  - X11 development packages
- **Math and geometry libraries**
  - Eigen
  - GLM
  - libigl headers cloned into /opt/libigl
- **Development utilities**
  - Git
  - Curl
  - Starship shell prompt configuration

The final working directory inside the container is `/workspace`, where the project files are mounted when running the container.

The resulting environment contains everything required to compile and run the `OpenGL` + `libigl` application without manually installing dependencies on the host system.

After the image is created, the project can be executed inside a Docker container with the same environment regardless of the host operating system.

## Running the container on Windows PowerShell

Before launching the container, make sure that both Docker Desktop and the X server are running. The X server is required because the graphical application runs inside the Docker container, but the display is provided by the host system. Make sure you **disable access control** on `VcXsrv`.

First, obtain the IPv4 address of the machine running the X server using:

```bash
ipconfig
```
Then launch the container with:
```powershell
docker run -it --rm -v "${PWD}:/workspace" -e DISPLAY=<IPv4>:0 libiglproj
```

Command breakdown:

- `docker run` reates and starts a new container from the specified Docker image.
- `-it` runs the container in interactive mode with an attached terminal.

- `--rm` automatically removes the container when it exits. This prevents unused stopped containers from accumulating.

- `-v "${PWD}:/workspace"` mounts the current host directory into the container, allowing files edited on the host machine to be directly available inside the container and vice versa:
  - *`${PWD}`* refers to the current directory on the host machine.
  - *`/workspace`* is the directory inside the container.

- `-e DISPLAY=<IPv4>:0` sets the `DISPLAY` environment variable inside the container, allowing graphical applications running inside Docker (such as OpenGL programs) to communicate with the host X server.

- `<IPv4>` should be replaced with your actual IPv4 address, obtained before.
- `:0` refers to the default display number.

The complete workflow is:

```text
Host machine 
-> X server
-> Docker container
-> GLFW/OpenGL application
-> Display output
```

## Running the container on Linux Bash
(TODO)