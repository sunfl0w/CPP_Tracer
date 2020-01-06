#include <string.h>
#include <iostream>
#include <thread>
#include <vector>

#include "Console.hpp"
#include "renderer.hpp"
#include "screenBuffer.hpp"
#include "camera.hpp"

using namespace OpenCG;
using namespace OpenCG::Math;
using namespace OpenCG::Rendering;

int main(int, char**) {
    int size = 40;
    Console console(size, size);
    Camera camera(Vec3(50, 0, 0), Vec3(1, 0, 0), Vec3(0, 1, 0));
    Renderer renderer = Renderer(size, size, &camera);

    std::vector<Tris> triangles = std::vector<Tris>();
    triangles.push_back(Tris(Vertex(0,0,0), Vertex(0,5,0), Vertex(0,0,5)));

    for (int i = 0; i < 100; i++) {
        console.ClearScreen();
        ScreenBuffer buffer = renderer.RenderToBuffer(triangles);
        console.DrawBuffer(buffer);

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}