### Readme of CPP_Tracer

#### Licsense
Information about the used license my be found in the LICENSE.md

#### Acknowledgements and license notices of third party software
Acknowledgements and license notices may be found in the Acknowledgements.md

#### Short description of CPP_Tracer
This is a somewhat small raytracer project that allows to load and render scenes composed of 3D objects via raytracing.
This can either be done on the CPU while utilizing several CPU-Cores or by the GPU with the help of a GLSL shader program.
The code is heavily inspired by the work on https://www.scratchapixel.com/ , it is a great website for learning commputer graphics.

#### Images
![Imgur](https://i.imgur.com/ZIm1xfF.png)
![Imgur](https://i.imgur.com/WvKWcG7.png)

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

#### Limitations of the GPU raytracer
To reach acceptable performance nubers the GPU variant will only compute refractive or reflective rays as a direct result of another ray. A raytraced scene might therefore look different when comparing the CPU and the GPU raytracer. The GPU raytracer also only supports alimited number of lights, meshes, triangles and spheres. Those are predefined values that can be changed by editing the raytracerGPU header and the raytracingSimple compute shader. The limits needed to be set so the compute shader can actually work. A GLSL shader only supports fixed lenght arrays in that case.

#### Performance
The performance is not great. The CPU version is really slow and also the GPU version is not that much better. Especially meshes are really expensive to raytrace. Limiting the recursive ray depth to 5 really helps with mirrors but also cuts back on realism. One can improve the reytracing performance by adjusting the values in the compute shader for the GPU or editing the glDispatchCompute call. One can also further limit the recursive depth.

#### Will there be further development?
Not really. I might improve performance by using bounding volumes (or by immproving existing code) and other neat little tricks but do not count on that as I am really glad to have brought this project to a state I am satisfied with and I really want to do other stuff for now. I think building a raytracer is a nice exercise for a few months to get used to a graphics API and learn something about the presummable future of graphics in general.