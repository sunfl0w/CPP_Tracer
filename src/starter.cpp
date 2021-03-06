#include <SDL2/SDL.h>
#include <glad/glad.h>
#include <string.h>

#include <boost/program_options.hpp>
#include <chrono>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <vector>

#include "bitmapFont.hpp"
#include "bitmapTextRenderer.hpp"
#include "mesh.hpp"
#include "meshObject.hpp"
#include "openGLDebug.hpp"
#include "raytracerCPU.hpp"
#include "raytracerGPU.hpp"
#include "renderingMode.hpp"
#include "scene.hpp"

using namespace Tracer;
using namespace Tracer::Rendering;
using namespace Tracer::Components;
using namespace Tracer::Rendering::Text;

using namespace boost::program_options;

int main(int argc, char* argv[]) {
    //Defining and hendeling program program
    options_description optionsDesribtion("Raytracer options");
    optionsDesribtion.add_options()("help,h", "Help Screen")("screenWidth,x", value<unsigned int>()->default_value(600), "The width of the rendering window")("screenHeight,y", value<unsigned int>()->default_value(400), "The height of the rendering window")("renderingMode,r", value<std::string>()->default_value("CPU"), "Type of rendering: CPU/GPU")("allowFPS,f", "Enables/Disables the fps counter")("scenePath,p", value<std::string>(), "Path to the scene to load and render.");

    variables_map variableMap;
    store(command_line_parser(argc, argv).options(optionsDesribtion).run(), variableMap);

    int screenWidth = 0;
    int screenHeight = 0;
    RenderingMode renderingMode = RenderingMode::CPU;
    bool showFPSCounter = false;
    std::string scenePath;

    if (variableMap.count("screenWidth")) {
        screenWidth = variableMap["screenWidth"].as<unsigned int>();
    }
    if (variableMap.count("screenHeight")) {
        screenHeight = variableMap["screenHeight"].as<unsigned int>();
    }
    if (variableMap.count("renderingMode")) {
        std::string renderingModeString = variableMap["renderingMode"].as<std::string>();
        if (renderingModeString == "CPU") {
            renderingMode = RenderingMode::CPU;
        } else if (renderingModeString == "GPU") {
            renderingMode = RenderingMode::GPU;
        } else {
            std::cout << "Wrong rendering mode specified\n";
            exit(1);
        }
    }
    if (variableMap.count("allowFPS")) {
        showFPSCounter = true;
    }
    if(variableMap.count("scenePath")) {
        scenePath = variableMap["scenePath"].as<std::string>();
    }

    //Defining a test scene
    Scene scene = Scene();
    scene.LoadSceneDataFromFile(scenePath);

    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    SDL_Window* window = SDL_CreateWindow("CPP_Tracer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, SDL_WINDOW_OPENGL);
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
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    BitmapFont bitmapFont = BitmapFont("resources/textures/SimpleAsciiFont.png", 8);
    BitmapTextRenderer bitmapTextRenderer = BitmapTextRenderer(bitmapFont, window);

    Raytracer* raytracer = new RaytracerCPU(window);
    if (renderingMode == RenderingMode::GPU) {
        raytracer = new RaytracerGPU(window);
    }

    std::stringstream stream;

    std::chrono::steady_clock::time_point start;
    float delta = 0.0f;
    bool running = true;

    start = std::chrono::steady_clock::now();
    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            } else if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    running = false;
                }
            }
        }
        scene.Update(delta);

        glClear(GL_COLOR_BUFFER_BIT);

        raytracer->RenderSceneToWindow(scene);

        delta = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::steady_clock::now() - start).count() * std::pow(10.0, -9);
        start = std::chrono::steady_clock::now();

        if (showFPSCounter) {
            std::string fps = std::to_string((int)(1.0f / delta));
            bitmapTextRenderer.DrawText("FPS: " + fps, glm::vec2(0, 0), glm::vec2(16, 16));
        }

        SDL_GL_SwapWindow(window);
    }
    delete raytracer;
    return 0;
}