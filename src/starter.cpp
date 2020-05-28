#include <SDL2/SDL.h>
#include <glad/glad.h>
#include <string.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <thread>
#include <vector>

#include "mesh.hpp"
#include "raytracer.hpp"
#include "rgb_Color.hpp"
#include "scene.hpp"
#include "screenBuffer.hpp"

using namespace Tracer;
using namespace Tracer::Math;
using namespace Tracer::Rendering;
using namespace Tracer::Components;

void APIENTRY GLDebugMessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* data) {
        std::string sourceType;
        std::string errorType;
        std::string severityType;

        switch (source) {
            case GL_DEBUG_SOURCE_API:
                sourceType = "API";
                break;

            case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
                sourceType = "WINDOW SYSTEM";
                break;

            case GL_DEBUG_SOURCE_SHADER_COMPILER:
                sourceType = "SHADER COMPILER";
                break;

            case GL_DEBUG_SOURCE_THIRD_PARTY:
                sourceType = "THIRD PARTY";
                break;

            case GL_DEBUG_SOURCE_APPLICATION:
                sourceType = "APPLICATION";
                break;

            case GL_DEBUG_SOURCE_OTHER:
                sourceType = "UNKNOWN";
                break;

            default:
                sourceType = "UNKNOWN";
                break;
        }

        switch (type) {
            case GL_DEBUG_TYPE_ERROR:
                errorType = "ERROR";
                break;

            case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
                errorType = "DEPRECATED BEHAVIOR";
                break;

            case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
                errorType = "UDEFINED BEHAVIOR";
                break;

            case GL_DEBUG_TYPE_PORTABILITY:
                errorType = "PORTABILITY";
                break;

            case GL_DEBUG_TYPE_PERFORMANCE:
                errorType = "PERFORMANCE";
                break;

            case GL_DEBUG_TYPE_OTHER:
                errorType = "OTHER";
                break;

            case GL_DEBUG_TYPE_MARKER:
                errorType = "MARKER";
                break;

            default:
                errorType = "UNKNOWN";
                break;
        }

        switch (severity) {
            case GL_DEBUG_SEVERITY_HIGH:
                severityType = "HIGH";
                break;

            case GL_DEBUG_SEVERITY_MEDIUM:
                severityType = "MEDIUM";
                break;

            case GL_DEBUG_SEVERITY_LOW:
                severityType = "LOW";
                break;

            case GL_DEBUG_SEVERITY_NOTIFICATION:
                severityType = "NOTIFICATION";
                break;

            default:
                severityType = "UNKNOWN";
                break;
        }
        std::cout << "Error/Notification" << "\n";
        std::cout << "ID: " << id << "\n";
        std::cout << "Type: " << errorType << "\n";
        std::cout << "Severity: " << severityType << "\n";
        std::cout << "Origin: " << source << "\n";
        std::cout << "Message: " << message << "\n";
        std::cout << "------------------" << "\n";
    }

int main() {
    std::vector<Objects::RenderableObject> renderableObjects;
    Mesh mesh;
    mesh.LoadFromObjectFile("./models/Sphere.obj");
    std::cout << "Triangles to render:" + std::to_string(mesh.GetData().size()) << std::endl;
    Objects::RenderableObject model = Objects::RenderableObject(glm::vec3(0.0f, 0.0f, 0.0f), mesh, Material::Material(Material::MaterialType::Refractive, Tracer::Components::Color::Color(100, 200, 50)));
    renderableObjects.push_back(model);

    std::vector<Objects::PointLight*> pointLights;
    Objects::PointLight light = Objects::PointLight(glm::vec3(10.0f, 0.0f, -10.0f), 1.0f, Components::Color::RGB_Color(0, 255, 0));
    pointLights.push_back(&light);
    Objects::PointLight light2 = Objects::PointLight(glm::vec3(-10.0f, 0.0f, -10.0f), 1.0f, Components::Color::RGB_Color(255, 220, 100));
    pointLights.push_back(&light2);

    Objects::Camera camera = Objects::Camera(glm::vec3(-5.0f, 0.0f, -15.0f), glm::vec3(10.0f, 0.0f, -10.0f));
    Scene scene = Scene(renderableObjects, pointLights, camera);

    Raytracer raytracer;

    SDL_Window* window;
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

#ifdef ENABLE_OPENGL_DEBUG
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);
#endif

    window = SDL_CreateWindow("Mill", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 400, SDL_WINDOW_OPENGL);
    SDL_GLContext glContext = SDL_GL_CreateContext(window);

    if (!gladLoadGL()) {
        std::cout << "Unable to load OpenGL\n";
    }

#ifdef ENABLE_OPENGL_DEBUG
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(GLDebugMessageCallback, 0);
#endif

    std::chrono::steady_clock::time_point start;
    float frameDelta = 0.0f;

    bool close = false;
    while (!close) {
        start = std::chrono::steady_clock::now();

        std::vector<sf::Event> events = std::vector<sf::Event>();

        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                close = true;
            } else if (event.type == SDL_WINDOWEVENT_RESIZED) {
                //glViewport(0, 0, event.window.data1, event.window.data2);
            }
        }
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        int width = 0;
        int height = 0;
        SDL_GetWindowSize(window, &width, &height);

        std::vector<unsigned char> screenBuffer = raytracer.RenderSceneToBuffer(scene, width, height);

        frameDelta = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start).count();
        //std::cout << "FPS: " << std::to_string(1000.0f / delta) << "\n";

        SDL_GL_SwapWindow(window);
    }
    return 0;
}
