### Readme of CPP_Tracer

#### Licsense
Information about the used license my be found in the LICENSE.md

#### Acknowledgements and license notices of third party software
Acknowledgements and license notices may be found in the Acknowledgements.md

#### Short description of CPP_Tracer
This is a somewhat small raytracer project that allows to load and render scenes composed of 3D objects via raytracing.
This can either be done on the CPU while utilizing several CPU-Cores or by the GPU with the help of a GLSL shader program.

#### Controls
The renderer my be exited by closing the window or by pressing ESC.

#### Options
- help,h => Help
- screenWidth,x => The width of the rendering window as an int
- screenHeight,y => The height of the rendering window as an int
- renderingMode,r => Specifies the rendering device. Either GPU/CPU as a string
- allowFPS,f => If specified the window will show and FPS counter
- scenePath,p => The path to the scene to render. The path needs to be absolute or relative to the executable

#### Defining your own scene
One can create a scene by creating a xml file describing the objects in that scene. The sample scenes are good as a reference point for that. Paths to meshes in a scene file do not need to be absolute or relative, all of them will be converted to absolute paths. So the paths just need to be valid.

#### Using meshes
The meshes to render need to made out of triangles only. Only obj files are allowed.