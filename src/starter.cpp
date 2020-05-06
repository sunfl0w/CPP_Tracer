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
    std::vector<Objects::RenderableObject> renderableObjects;
    Mesh mesh;
    mesh.LoadFromObjectFile("./models/Sphere.obj");
    std::cout << "Triangles to render:" + std::to_string(mesh.GetData().size()) << std::endl;
    Objects::RenderableObject model = Objects::RenderableObject(Math::Vec3(0, 0, 0), mesh, Material::Material(Material::MaterialType::Refractive, Tracer::Components::Color::Color(100, 200, 50)));
    renderableObjects.push_back(model);

    std::vector<Objects::PointLight*> pointLights;
    Objects::PointLight light = Objects::PointLight(Math::Vec3(10, 0, -10), 0.001f, Components::Color::Color(255, 255, 75));
    pointLights.push_back(&light);
    //Objects::PointLight light2 = Objects::PointLight(Math::Vec3(-10, 0, 10), 1.0f, Components::Color::Color(255, 220, 100));
    //pointLights.push_back(&light2);

    Objects::Camera camera = Objects::Camera(Math::Vec3(-5, 0, -15), Math::Vec3(10, 0, -10));
    Scene scene = Scene(renderableObjects, pointLights, camera);

    Raytracer raytracer;

    int width = 600;
    int height = 400;

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

    while (window.isOpen()) {
        start = std::chrono::steady_clock::now();
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        //light.GetTransform().Translate(Math::Vec3(-1.1f, 0.0f, 0));
        light.GetTransform().Rotate(0, 1.0f, 0);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            scene.GetCamera().GetTransform().Translate(Math::Vec3(-0.05f, 0, 0));
            //std::cout << "Left" << std::endl;
            //lightPos = lightPos.Add(Math::Vec3(-0.5f, 0, 0));
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            scene.GetCamera().GetTransform().Translate(Math::Vec3(0.05f, 0, 0));
            //std::cout << "Right" << std::endl;
            //lightPos = lightPos.Add(Math::Vec3(0.5f, 0, 0));
        }

        window.clear(sf::Color::Black);

        ScreenBuffer buffer = raytracer.RenderSceneToBuffer(scene, width, height);
        texture.update(buffer.GetBufferData());
        fpsText.setString("FPS: " + std::to_string(1000.0f / frameDelta));

        window.draw(sprite);
        window.draw(fpsText);

        frameDelta = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start).count();
        window.display();
    }
    return 0;
}