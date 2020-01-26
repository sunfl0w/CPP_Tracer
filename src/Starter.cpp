#include <string.h>

#include <SFML/Graphics.hpp>
#include <iostream>
#include <thread>
#include <vector>

#include "mesh.hpp"
#include "raytracer.hpp"
#include "screenBuffer.hpp"

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

    int width = 800;
    int height = 600;

    sf::RenderWindow window(sf::VideoMode(width, height), "CPP_Tracer");
    sf::Text fpsText;
    fpsText.setFillColor(sf::Color::White);
    fpsText.setCharacterSize(16);
    sf::Font font;
    font.loadFromFile("./Fonts/SourceCodePro-Bold.ttf");
    fpsText.setFont(font);

    std::chrono::steady_clock::time_point start;
    float frameDelta = 0.0f;

    sf::Texture texture;
    texture.create(width, height);
    sf::Sprite sprite(texture);
    Math::Vec3 camPos(0, 0, -14);

    while (window.isOpen()) {
        start = std::chrono::steady_clock::now();
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            camPos = camPos.AddOther(Math::Vec3(-0.5f, 0, 0));
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            camPos = camPos.AddOther(Math::Vec3(0.5f, 0, 0));
        }

        window.clear(sf::Color::Black);



        ScreenBuffer buffer = raytracer.RenderToBuffer(mesh.GetData(), width, height, camPos);
        texture.update(buffer.GetBufferData());
        fpsText.setString("FPS: " + std::to_string(1000.0f / frameDelta));

        window.draw(sprite);
        window.draw(fpsText);

        frameDelta = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start).count();
        window.display();
    }
    return 0;
}