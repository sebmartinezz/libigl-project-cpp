@echo off

docker run --rm -it ^
    -v "%cd%:/workspace" ^
    -e DISPLAY=host.docker.internal:0.0 ^
    libiglproj