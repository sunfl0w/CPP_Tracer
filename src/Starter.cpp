#include <string.h>
#include <iostream>
#include <thread>
#include <vector>

#include "Console.hpp"
#include "Pixel.hpp"
#include "PixelScreenBuffer.hpp"
#include "RGB_Color.hpp"

#include "camera.hpp"
#include "projector.hpp"
#include "viewport.hpp"

#include "matrix.hpp"

using namespace OpenCG;
using namespace OpenCG::Math;
using namespace OpenCG::Renderer;

int main(int, char**) {
    /*for (int r = 0; r < 256; r+= 16) {
        for (int g = 0; g < 256; g+= 16) {
            for (int b = 0; b < 256; b+= 16) {
                std::string colorString = "\033[38;2;" + std::to_string(r) + ";" + std::to_string(g) + ";" + std::to_string(b) + "m#";
                std::cout << colorString;
            }
        }
    }
    std::cout << "\033[38;5;4;176;2mHello";*/
    int size = 20;
    Console console(size, size);
    Matrix point(1, 4, std::vector<float>{5, 0, 5, 1});

    for (int i = 0; i < 100; i++) {
        point = Matrix(1, 4, std::vector<float>{5, point.GetData()[1] - 0.5f, 5, 1});

        Projector projector(size, size, 1, 100);
        Camera camera(Vec3(0, 0, 0), Vec3(1, 0, 0), Vec3(0, 1, 0));
        Viewport viewport(size, size, 1, 100);

        Matrix protoPixel = projector.GetMatrix().MultiplyWith(camera.GetMatrix().MultiplyWith(point));
        Vec3 pixel = viewport.TransformPoint(Vec3(protoPixel.GetData()[0], protoPixel.GetData()[1], protoPixel.GetData()[2]));
        //Matrix pixel = camera.GetMatrix().MultiplyWith(point);

        int x1 = std::round(pixel.X());
        int y1 = std::round(pixel.Y());

        PixelScreenBuffer buffer(size, size);
        std::vector<Pixel> bufferData = std::vector<Pixel>(size * size);
        for (int x = 0; x < size; x++) {
            for (int y = 0; y < size; y++) {
                if (x == std::round(pixel.X()) && y == std::round(pixel.Y())) {
                    bufferData[x + y * size] = Pixel(RGB_Color(200, 100, 100));
                } else {
                    bufferData[x + y * size] = Pixel(RGB_Color(50, 50, 50));
                }
            }
        }
        buffer.SetBufferData(bufferData);

        console.ClearScreen();
        console.DrawBuffer(buffer);

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}