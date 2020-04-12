#include <string.h>

#include <SFML/Graphics.hpp>
#include <iostream>
#include <thread>
#include <vector>

#include "mesh.hpp"
#include "raytracer.hpp"
#include "screenBuffer.hpp"
#include "scene.hpp"

using namespace Tracer;
using namespace Tracer::Math;
using namespace Tracer::Rendering;
using namespace Tracer::Components;

int main() {
    Scene scene = Scene();
    
    Objects::Object model = Objects::Object("Model");
    Mesh mesh;
    mesh.LoadFromObjectFile("./models/Sphere.obj");
    std::cout << "Triangles to render:" + std::to_string(mesh.GetData().size()) << std::endl;
    model.AddComponent(mesh);
    model.AddComponent(Components::Positioning::Transform(Math::Vec3(0, 0, 0)));
    scene.AddObject(model);

    Objects::Camera camera = Objects::Camera(Math::Vec3(-5, 0, -15), Math::Vec3(0, 0, 0));
    scene.AddObject(camera);
    Objects::PointLight light = Objects::PointLight(Math::Vec3(10, 0, -10), 1.0f);
    scene.AddObject(light);

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

    while (window.isOpen()) {
        start = std::chrono::steady_clock::now();
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            camera.GetComponent("TransformComponent") = camPos.Add(Math::Vec3(-0.5f, 0, 0));
            //std::cout << "Left" << std::endl;
            //lightPos = lightPos.Add(Math::Vec3(-0.5f, 0, 0));
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            camPos = camPos.Add(Math::Vec3(0.5f, 0, 0));
            //std::cout << "Right" << std::endl;
            //lightPos = lightPos.Add(Math::Vec3(0.5f, 0, 0));
        }

        window.clear(sf::Color::Black);

        ScreenBuffer buffer = raytracer.RenderToBuffer(meshes, width, height, camPos, lightPos);
        texture.update(buffer.GetBufferData());
        fpsText.setString("FPS: " + std::to_string(1000.0f / frameDelta));

        window.draw(sprite);
        window.draw(fpsText);

        frameDelta = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start).count();
        window.display();
    }
    return 0;
}