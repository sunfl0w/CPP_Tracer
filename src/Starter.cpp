#include <string.h>
#include <iostream>
#include <thread>
#include <vector>

#include "Console.hpp"
#include "screenBuffer.hpp"
#include "mesh.hpp"
#include "raytracer.hpp"

using namespace OpenCG;
using namespace OpenCG::Math;
using namespace OpenCG::Rendering;
using namespace OpenCG::Components;

int main(int, char**) {
    Mesh mesh;
    mesh.LoadFromObjectFile("/home/sunfl0w/Cube.obj");

    int size = 30;
    Console console(size, size);
    Raytracer raytracer;

    for (int i = 0; i < 100; i++) {
        console.ClearScreen();
        ScreenBuffer buffer = raytracer.RenderToBuffer(mesh.GetData(), size, size);
        console.DrawBuffer(buffer);

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}