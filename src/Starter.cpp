#include <string.h>
#include <iostream>
#include <thread>
#include <vector>
#include <SFML/Graphics.hpp>

#include "screenBuffer.hpp"
#include "mesh.hpp"
#include "raytracer.hpp"

using namespace OpenCG;
using namespace OpenCG::Math;
using namespace OpenCG::Rendering;
using namespace OpenCG::Components;

int main() {
    Mesh mesh;
    mesh.LoadFromObjectFile("/home/sunfl0w/Cube.obj");
    std::vector<Tris> triangles;
    triangles.push_back(Tris(Vertex(-5, -5, 5), Vertex(-5, 10, 5), Vertex(10, -5, 5)));
    /*Ray ray = Ray(Math::Vec3(0, 0, 0), Math::Vec3(0, 0, 1), 100);
    IntersectData intersectData = ray.Cast(triangles[0]);
    int i = 0;*/
    Raytracer raytracer;

    int width = 400;
    int height = 300;

    sf::RenderWindow window(sf::VideoMode(width, height), "CPP_Tracer");

    sf::Texture texture;
    texture.create(width, height);
    sf::Sprite sprite(texture);

    while(window.isOpen()) {
        sf::Event event;
        while(window.pollEvent(event)) {
            if(event.type == sf::Event::Closed) {
                window.close();
            }
        }
        window.clear(sf::Color::Black);
        ScreenBuffer buffer = raytracer.RenderToBuffer(mesh.GetData(), width, height);
        texture.update(buffer.GetBufferData());
        window.draw(sprite);

        window.display();
        std::cout << "RENDERED!\n";
    }
    return 0;
}