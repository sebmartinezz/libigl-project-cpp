# Use Ubuntu 24.04 as base image
FROM ubuntu:24.04

# Avoid interactive prompts during installation
ENV DEBIAN_FRONTEND=noninteractive

# Update package list and install dependencies
# ¡Quitamos libglad-dev de aquí para evitar el error!
RUN apt update && apt install -y \
    software-properties-common \
    g++-14 \
    curl \
    build-essential \
    cmake \
    pkg-config \
    git \
    libeigen3-dev \
    libgl1-mesa-dev \
    libglu1-mesa-dev \
    mesa-utils \
    libglfw3-dev \
    xorg-dev \
    && rm -rf /var/lib/apt/lists/*

# En Ubuntu 24.04, forzamos que g++ apunte a g++-14
RUN update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-14 100 \
    --slave /usr/bin/g++ g++ /usr/bin/g++-14

# Installing starship
RUN curl -sS https://starship.rs/install.sh | sh -s -- --yes
RUN echo 'eval "$(starship init bash)"' >> /root/.bashrc

# Solo clonamos las cabeceras (.h) de libigl (Tardará 5 segundos)
RUN git clone --depth 1 https://github.com/libigl/libigl.git /opt/libigl

# Set working directory
WORKDIR /workspace

# Default command
CMD ["/bin/bash"]