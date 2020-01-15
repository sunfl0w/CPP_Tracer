#include <string.h>
#include <iostream>
#include <thread>
#include <vector>

#include "Console.hpp"
#include "renderer.hpp"
#include "screenBuffer.hpp"
#include "camera.hpp"
#include "mesh.hpp"

using namespace OpenCG;
using namespace OpenCG::Math;
using namespace OpenCG::Rendering;
using namespace OpenCG::Components;

int main(int, char**) {
    Mesh mesh;
    mesh.LoadFromObjectFile("/home/sunfl0w/Cube.obj");

    int size = 30;
    Console console(size, size);
    Camera camera(Vec3(1, 1, 0), Vec3(-1, 0, 0), Vec3(0, 1, 0));
    Renderer renderer = Renderer(size, size, 90.0f, &camera);

    for (int i = 0; i < 100; i++) {
        console.ClearScreen();
        ScreenBuffer buffer = renderer.RenderToBuffer(mesh.GetData());
        console.DrawBuffer(buffer);

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}