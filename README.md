# WebGL C Game Engine


<image src="media/maze2.webp" width="256"></image>
<image src="media/terrain.webp" width="256"></image>

## About

This WebGL game engine is the collective result of several demo projects, written in C using [Emscripten's](https://emscripten.org/docs/tools_reference/emcc.html) C compiler in order to compile to WebAssembly with included Javascript Wrappers for the C standard library. Developed over a 4 month semester for my CS-3600 Graphics Class, this engine provides enough features to develop full games, as shown in the following demos, and is very capable of being extended into adding more features.

The reason this engine and subsiquent demos were developed for a web enviroment rather than in a native enviroment like Windows or Linux, is because the graphics class at my university switched to using WebGL and Javascript. And most of the assignments were already half written by the professor, only requiring the student to modify the code in order to complete the semester coursework. I was not a big fan of this learning approach, and was very eager to teach myself how to design a reusable graphics engine API <ins>completely from scratch</ins> using a fast native language like C, while still being able to fullfill the requirements of the class of the application being able to run in a web enviroment.

Using C and the Emscripten compiler, I was able to spare myself the horrors of having to develop a graphical application in an untyped language. Compiling to WebAssembly I was able to give myself a more native and from-scratch experience of developing optimized graphical applications.

During this process, I have learned the OpenGL API, as well as the GLSL scripting language.

The intention of this engine is to make it reusable, in order to speed up the development of the assignments throughout the course of this semester. Using the API I've written, it is much easier to streamline the process of designing 3D graphic projects.




## Demos

The following are links to playable demos that you can run in your browser. They have only been tested in Firefox and Chromium, as well as a limited pool of devices. <ins>Warning: There have been some reports from playtesters with particular graphics cards where certain shaders or textures failed to render properly.</ins> So compatability is not guaranteed.

As per my artistic preference, most of these projects are rendered in a low resolution, using harsh pixelated textures and dithering in order to give it more of a retro aesthetic. 

### Bouncing Balls Demo

The Bouncing Balls demo laid the foundations of this engine. And in terms of core functionality, is what implemented the most features to the API. Initially the demo was in 2D, but I did such a good job with the physics that the balls started bouncing along a third axis and into a new dimension outside of the viewport clip range, which prompted me to transition it to 3D. <ins>The demo is non-interactive unless you are on mobile</ins>, in which case the orientation of your phone determines gravity.

<image src="media/balls.webp" width="200"></image>

[Play Bouncing Balls Demo in Browser](https://stephen010x.github.io/projects/webgl-c-frame/balls)

### Bezier Curves Demo

This demo showcases 3D cubic bezier curves, where the points randomly drift around. This one isn't too special. It was just one of the assignments, and didn't make any huge changes or advancements to the engine. This demo is interactive.

<image src="media/bezier.webp" width="200"></image>

[Play Bezier Cruves Demo in Browser](https://stephen010x.github.io/projects/webgl-c-frame/bezier)

### Fractal Zoom Demo

This demo showcases an *interactive* Mandelbrot fractal zoom. This was mostly an excercise of the GLSL shading language, and ultimately did not contribute any new features to the engine.\
(P.S. Beware of floating point limitations.)

<image src="media/fractal.webp" width="200"></image>

[Play Fractal Zoom Demo in Browser](https://stephen010x.github.io/projects/webgl-c-frame/fractal)

## 3D Maze Demo

The 3D Maze Demo is a combination of multiple assignments thoroughout the class, combined into one demo (which is why it has multiple modes). This demo inroduced the biggest changes to the engine since the initial [Bouncing Balls Demo](#bouncing-balls-demo). It introduced textures, framebuffers with virtual cameras that can render to them, framebuffer textures, instanced light sources, normal maps, 

This demo demonstrates random maze generation with rooms, lighting shaders that perform dynamic normal-map lighting, point light sources, drawing a paint trail to a texture, virtual viewport cameras that can render to a texture (used for a mirror at the end of the maze), as well as a strong enviromental atmosphere with dramatic lighting, animations, and sound design.

(P.S. The character and hand sprites were drawn by me, but the wall textures and sound effects were obtained from free external sources)

<image src="media/maze1.webp" width="200"></image>
<image src="media/maze2.webp" width="200"></image>

[Play 3D Maze Demo in Browser](https://stephen010x.github.io/projects/webgl-c-frame/maze)

## Terrain Demo

While not as impactful to the engine as the [3D Maze Demo](#3d-maze-demo), the Terrain demo refines some of the concepts of the previous demo. Particularly with lighting sources by improving on the normal map shader code to be more versatile and robus, adding the Blinn–Phong spectral shading model, as well as implementing occlusion maps to improve the lighting aesthetic.

As an end result, I feel I've achieved a pleasing aesthetic with the terrain. I added logic in the shaders for implementing cliffs, grass, sand, and wetstone. And I added water wave animations, alongside linear depth fog for the water with dithering for style, and similar fog effects when underwater.

The terrain generation used sinusoidal generation rather than noise. This decision was made simply because noise generation is a concept that I didn't want to research at the time, and I already had a good idea of how to use sinusoids to generate realistic looking terrain.

The formula I eventually derived for the terrain generation:
```math
\begin{align*}
&\quad\text{Given an } x\in\mathbb{R} \text{ and } y\in\mathbb{R}, \\
&\quad\text{Let } P, H, \text{ and } N \text{ denote sets all of equal size to describe} \\
&\quad\text{the generation.}\\
&z=\!\!\sum^{|P|}_{n=1}H_n\cdot\Bigg(\sin\Bigg(\frac{x+H_n\cdot\cos\big(\frac{y}{P_n}\big)}{P_n}\Bigg)^{N_n}+\cos\Bigg(\frac{y-H_n\cdot\cos\big(\frac{x}{P_n}\big)}{P_n}\Bigg)^{N_n}\Bigg)
\end{align*}
```
<br>
All of the texture assets were obtained from free external sources.
<br>
<br>

<image src="media/graph.webp" width="200" alt="graph.webp"></image>
<image src="media/terrain.webp" width="200"></image> \
First image courtesy of [Desmos 3D Calculator](https://www.desmos.com/3d)

[Play Terrain Demo in Browser](https://stephen010x.github.io/projects/webgl-c-frame/terrain)

## Chess Set Demo

The Chess Set Demo was the final project in this series, adding the final feature to this engine, which is the ability to load .obj meshes into a scene. I originally wanted to add physics to this demo to make it more interactable with the user. But I ran out of time to implement this, so I left it as a static scene.

All the models in this demo were obtained from free external sources, and subsequently modified by me using [Blender](https://www.blender.org/download/)

<image src="media/chess.webp" width="200"></image>

[Play Chess Set Demo in Browser](https://stephen010x.github.io/projects/webgl-c-frame/chess)




## Documentation

The following contains links to the API documentation for this project. However, with this project fresh out of the oven that was this last Spring semester, as of writing there has not been a lot of time to fully document the types and functions of this API, and I plan to incrementally add to the documentation of the course of the summer.

[Link to Documentation](docs/docs.md)

## Notice of development

Development of this project will halt in favor of completely rewriting this project to a native enviroment like Linux, with a more robust, complete, and unrushed set of features before I plan to reimplement web compatability with this engine.

## Previews

<image src="media/balls.gif" width="256" height="256" alt="balls.gif"></image>
<image src="media/chess.gif" width="256" alt="chess.gif"></image> \
<image src="media/bezier.gif" width="256" height="256" alt="bezier.gif"></image>
<image src="media/fractal.gif" width="256" height="256" alt="fractal.gif"></image> \
<image src="media/maze1.gif" width="256" height="256" alt="maze1.gif"></image>
<image src="media/maze3.gif" width="256" height="256" alt="maze3.gif"></image> \
<image src="media/maze4.gif" width="256" height="256" alt="maze4.gif"></image>
<image src="media/terrain1.gif" width="256" height="256" alt="terrain1.gif"></image> \
<image src="media/terrain2.gif" width="256" height="256" alt="terrain2.gif"></image>
<image src="media/terrain3.gif" width="256" height="256" alt="terrain3.gif"></image>

<!--image src="media/maze2.gif" width="256" height="256" alt="maze2.gif"></image-->
<!--image src="media/terrain4.gif" width="256" height="256" alt="terrain4.gif"></image-->
