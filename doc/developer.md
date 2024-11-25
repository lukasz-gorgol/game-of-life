# Developer Guide

## VS Code Extensions

* C/C++ Extensions Pack
* Clang-Format
* CMake
* Cmake Tools
* CodeLLDB
* GitLens - Git supercharged
* Makefile Tools
* vscode-icons

## Prerequisities

```bash
sudo apt install libsdl2-2.0-0 libsdl2-dev libsdl-doc libsdl-gfx-1.0-0 libsdl2-gfx-dev libsdl2-gfx-doc libsdl2-image-2.0-0 libsdl2-image-dev libsdl2-mixer-2.0-0 lib sdl2-mixer-dev libsdl2-net-2.0-0 libsdl2-net-dev libsdl2-ttf-2.0-0 libsdl2-tth-dev nlohmann-json3-dev
```

## Build and Run

```bash
cd build
cmake ..
make
./GameOfLife
```

## Compile by Hand

```bash
cd src
g++ *.cpp -std=c++20 -lSDL2 $(sdl2-config --cfalgs --libs)
# make sure to bring assets/config.json together with a.out file
```

[*back to main*](../README.md)