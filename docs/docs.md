# WebGL C Frame Documentation

## About

WebGL C Frame, or "WebGL C Framework", is a small WebGL and WebASM 3D engine built around WebGL and [Emscripten](https://emscripten.org/). This API is written in C, for C. It is intended to be compiled with Emscripten's compiler, [emcc](https://emscripten.org/docs/tools_reference/emcc.html). This ultimately allows for a fast and optimized multi-platform browser-based 3D or 2D games to be developed and compiled into WebASM and JavaScript.

## Core Documentation

These are the core files and functions of the system, and act as the vital components of the engine.

&emsp; [Audio API](core/audio.md) \
&emsp; [Camera/Lightsource API](core/camera.md) \
&emsp; [Files API](core/files.md) \
&emsp; [Input API](core/input.md) \
&emsp; [Model API](core/model.md) \
&emsp; [Physics API](core/physics.md) \
&emsp; [Shader API](core/shader.md) \
&emsp; [Texture API](core/texture.md) \
&emsp; [Enviroment API](core/enviroment.md)

## Object Documentation

These are objects or classes that were generally designed around specific projects that this engine was used to build, and aren't neccissary for engine functionality.

&emsp; [Bezier Object](objects/bezier.md) \
&emsp; [DrawSurface Object](objects/drawsurface.md) \
&emsp; [Fractal Object](objects/fractal.md) \
&emsp; [Maze Object](objects/maze.md) \
&emsp; [Mouse Object](objects/mouse.md) \
&emsp; [Shapes Object](objects/shapes.md) \
&emsp; [Terrain Object](objects/terrain.md)
