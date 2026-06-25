# Use Ubuntu 24.04 as base image
FROM ubuntu:24.04

# Avoid interactive prompts during installation
ENV DEBIAN_FRONTEND=noninteractive

# Update package list and install dependencies
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
    libglm-dev\
    xorg-dev \
    && rm -rf /var/lib/apt/lists/*

# forcing g++ to point g++-14
RUN update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-14 100 \
    --slave /usr/bin/g++ g++ /usr/bin/g++-14

# installing starship and lazygit
RUN curl -sS https://starship.rs/install.sh | sh -s -- --yes
RUN echo 'eval "$(starship init bash)"' >> /root/.bashrc

ENV LAZYGIT_VERSION=0.43.1

RUN curl -Lo /tmp/lazygit.tar.gz \
    https://github.com/jesseduffield/lazygit/releases/download/v${LAZYGIT_VERSION}/lazygit_${LAZYGIT_VERSION}_Linux_x86_64.tar.gz && \
    tar -xzf /tmp/lazygit.tar.gz -C /tmp && \
    install /tmp/lazygit /usr/local/bin/lazygit && \
    rm -rf /tmp/lazygit*

# clone headers from libigl
RUN git clone --depth 1 https://github.com/libigl/libigl.git /opt/libigl

# set working directory ola
WORKDIR /workspace

# default command
CMD ["/bin/bash"]