#include <SDL2/SDL.h>
#include <glad/glad.h>
#include <stb_image.h>
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
#include "shader.hpp"

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
    std::cout << "Error/Notification"
              << "\n";
    std::cout << "ID: " << id << "\n";
    std::cout << "Type: " << errorType << "\n";
    std::cout << "Severity: " << severityType << "\n";
    std::cout << "Origin: " << source << "\n";
    std::cout << "Message: " << message << "\n";
    std::cout << "------------------"
              << "\n";
}

int main() {
    std::vector<Objects::RenderableObject> renderableObjects;
    Mesh mesh;
    mesh.LoadFromObjectFile("./models/Sphere.obj");
    std::cout << "Triangles to render:" + std::to_string(mesh.GetData().size()) << std::endl;
    Objects::RenderableObject model = Objects::RenderableObject(glm::vec3(0.0f, 0.0f, 0.0f), mesh, Material::Material(Material::MaterialType::Refractive, Tracer::Components::Color::RGB_Color(0.1f, 0.1f, 0.9f)));
    renderableObjects.push_back(model);
    Objects::RenderableObject model2 = Objects::RenderableObject(glm::vec3(3.0f, 3.0f, 0.0f), mesh, Material::Material(Material::MaterialType::Refractive, Tracer::Components::Color::RGB_Color(0.8f, 0.4f, 0.2f)));
    renderableObjects.push_back(model2);

    std::vector<Objects::PointLight*> pointLights;
    Objects::PointLight light = Objects::PointLight(glm::vec3(10.0f, 0.0f, -10.0f), 1.0f, Components::Color::RGB_Color(1.0f, 1.0f, 0.4f));
    pointLights.push_back(&light);
    //Objects::PointLight light2 = Objects::PointLight(glm::vec3(-10.0f, 0.0f, -10.0f), 1.0f, Components::Color::RGB_Color(255, 220, 100));
    //pointLights.push_back(&light2);

    Objects::Camera camera = Objects::Camera(glm::vec3(0.0f, 0.0f, -15.0f), glm::vec3(0.0f, 0.0f, 0.0f));
    Scene scene = Scene(renderableObjects, pointLights, camera);

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

    window = SDL_CreateWindow("CPP_Tracer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 400, SDL_WINDOW_OPENGL);
    SDL_GLContext glContext = SDL_GL_CreateContext(window);

    SDL_GL_SetSwapInterval(0);

    if (!gladLoadGL()) {
        std::cout << "Unable to load OpenGL\n";
    }

    Raytracer raytracer;

#ifdef ENABLE_OPENGL_DEBUG
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(GLDebugMessageCallback, 0);
#endif

    //OpenGL setup for rendering a texture
    unsigned int VAO, VBO, EBO, texture;
    float vertices[] = {
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, -1.0f, 1.0f, 0.0f,
        -1.0f, -1.0f, 0.0f, 0.0f,
        -1.0f, 1.0f, 0.0f, 1.0f};

    unsigned int indices[] = {
        0, 1, 3,
        1, 2, 3};

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_DYNAMIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    //Texture
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, 600, 400, 0, GL_RGBA, GL_FLOAT, NULL);
    glBindImageTexture(0, texture, 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_RGBA32F);
    glBindTexture(GL_TEXTURE_2D, 0);

    //Shaders
    Shader shader = Shader("resources/shaders/texture.vs", GL_VERTEX_SHADER, "resources/shaders/texture.fs", GL_FRAGMENT_SHADER);
    Shader computeShader = Shader("resources/shaders/raytracing.comp", GL_COMPUTE_SHADER);

    std::chrono::steady_clock::time_point start;
    float frameDelta = 0.0f;

    bool close = false;
    while (!close) {
        start = std::chrono::steady_clock::now();

        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                close = true;
            }
        }
        //computeShader.Activate();
        //raytracer.RenderSceneToImage(scene, 600, 400);
        //glDispatchCompute(600, 400, 1);
        //glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);

        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        std::vector<unsigned char> screenBuffer = raytracer.RenderSceneToBuffer(scene, 600, 400);
        shader.Activate();
        shader.SetInt("tex", 0);

        glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 600, 400, GL_RGB, GL_UNSIGNED_BYTE, screenBuffer.data());
        glBindVertexArray(VAO);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        SDL_GL_SwapWindow(window);

        frameDelta = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::steady_clock::now() - start).count();
        std::cout << "FPS: " << std::to_string(std::pow(10.0, 9) / frameDelta) << "\n";
    }
    return 0;
}
