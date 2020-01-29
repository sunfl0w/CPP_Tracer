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
    mesh.LoadFromObjectFile("./models/Cube.obj");
    std::vector<Mesh> meshes;
    meshes.push_back(mesh);
    Raytracer raytracer;

    int width = 1920;
    int height = 1080;

    sf::RenderWindow window(sf::VideoMode(width, height), "CPP_Tracer");
    sf::Text fpsText;
    fpsText.setFillColor(sf::Color::White);
    fpsText.setCharacterSize(16);
    sf::Font font;
    font.loadFromFile("./fonts/SourceCodePro-Bold.ttf");
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



        ScreenBuffer buffer = raytracer.RenderToBuffer(meshes, width, height, camPos);
        texture.update(buffer.GetBufferData());
        fpsText.setString("FPS: " + std::to_string(1000.0f / frameDelta));

        window.draw(sprite);
        window.draw(fpsText);

        frameDelta = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start).count();
        window.display();
    }
    return 0;
}