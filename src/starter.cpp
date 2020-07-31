#include <SDL2/SDL.h>
#include <glad/glad.h>
#include <string.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <vector>
#include <chrono>

#include "mesh.hpp"
#include "meshObject.hpp"
#include "scene.hpp"
#include "raytracerCPU.hpp"
#include "raytracerGPU.hpp"
#include "raytracerIterative.hpp"
#include "openGLDebug.hpp"

using namespace Tracer;
using namespace Tracer::Rendering;
using namespace Tracer::Components;

int main() {
    Scene scene = Scene();

    std::vector<Objects::RenderableObject> renderableObjects;
    Mesh mesh;
    mesh.LoadFromObjectFile("./models/Cube.obj");

    //Objects::MeshObject model = Objects::MeshObject(glm::vec3(3.0f, 0.0f, 0.0f), Material(glm::vec3(0.9f, 0.9f, 0.9f), 1.0f, 0.0f), mesh);
    //scene.AddMeshObject(model);
    Objects::MeshObject model2 = Objects::MeshObject(glm::vec3(0.0f, -3.0f, 0.0f), Tracer::Components::Material(glm::vec3(0.9f, 0.9f, 0.9f), 1.0f, 0.0f), mesh);
    model2.GetTransform().SetScale(glm::vec3(10, 1, 10));
    scene.AddMeshObject(model2);

    Objects::Sphere sphere = Objects::Sphere(glm::vec3(3.0f, 0.0f, 0.0f), Tracer::Components::Material(glm::vec3(0.1f, 0.9f, 0.9f), 0.0f, 0.0f), 1.0f);
    scene.AddSphere(sphere);
    //Objects::Sphere sphere2 = Objects::Sphere(glm::vec3(0.0f, 0.0f, 0.0f), Material(glm::vec3(0.9f, 0.2f, 0.9f), 1.0f, 0.0f), 1.0f);
    //scene.AddSphere(sphere2);
    Objects::Sphere sphere3 = Objects::Sphere(glm::vec3(0.0f, -1.0f, 3.0f), Tracer::Components::Material(glm::vec3(0.2f, 0.9f, 0.3f), 0.0f, 1.0f), 1.0f);
    scene.AddSphere(sphere3);
    Objects::Sphere sphere4 = Objects::Sphere(glm::vec3(0.0f, 3.0f, 2.0f), Tracer::Components::Material(glm::vec3(0.6f, 0.9f, 0.3f), 0.0f, 0.0f), 1.0f);
    scene.AddSphere(sphere4);

    Objects::PointLight light = Objects::PointLight(glm::vec3(10.0f, 0.0f, -10.0f), glm::vec3(1.0f, 1.0f, 0.4f), 1.0f);
    scene.AddPointLight(light);
    Objects::PointLight light2 = Objects::PointLight(glm::vec3(-10.0f, 0.0f, 6.0f), glm::vec3(0.8f, 0.8f, 0.8f), 1.0f);
    scene.AddPointLight(light2);

    Objects::Camera camera = Objects::Camera(glm::vec3(0.0f, 0.0f, -15.0f), glm::vec3(0.0f, 0.0f, 0.0f));
    scene.SetCamera(camera);

    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    SDL_Window* window = SDL_CreateWindow("CPP_Tracer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 400, SDL_WINDOW_OPENGL);
    SDL_GLContext glContext = SDL_GL_CreateContext(window);

    SDL_GL_SetSwapInterval(0);

    if (!gladLoadGL()) {
        std::cout << "Unable to load OpenGL\n";
        return -1;
    }

#ifdef ENABLE_OPENGL_DEBUG
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(Tarcer::Rendering::GLDebugging::GLDebugMessageCallback, 0);
#endif

    Raytracer* raytracer = new RaytracerCPU(window);
    //Raytracer* raytracer = new RaytracerGPU(window);
    //Raytracer* raytracer = new RaytracerIterative(window);

    std::chrono::steady_clock::time_point start;
    float delta = 0.0f;

    bool running = true;
    while (running) {
        start = std::chrono::steady_clock::now();

        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            } else if(event.type == SDL_KEYDOWN) {
                if(event.key.keysym.sym == SDLK_ESCAPE) {
                    running = false;
                }
            }
        }
        //When rotating around the the origin the position of a transform is not entirely correct!
        scene.GetCamera().GetTransform().RotateAroundOrigin(glm::vec3(0, 1, 0), delta * 20.0f);

        raytracer->RenderSceneToWindow(scene);

        delta = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::steady_clock::now() - start).count() * std::pow(10.0, -9);
        //std::cout << "FPS: " << std::to_string(1.0f / delta) << "\n";
    }
    delete raytracer;
    return 0;
}