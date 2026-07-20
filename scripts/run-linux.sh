#!/bin/bash

set -e

xhost +SI:localuser:root >/dev/null

cleanup() {
    xhost -SI:localuser:root >/dev/null
}

trap cleanup EXIT

docker run \
    --rm \
    -it \
    --device=/dev/dri \
    -e DISPLAY="$DISPLAY" \
    -v /tmp/.X11-unix:/tmp/.X11-unix \
    -v "$PWD:/workspace" \
    libiglproj