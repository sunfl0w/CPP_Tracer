#include <string.h>
#include <iostream>
#include <vector>

#include "Console.hpp"
#include "Pixel.hpp"
#include "PixelScreenBuffer.hpp"
#include "RGB_Color.hpp"

using namespace OpenCG;

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
    Console console(10, 10);
    console.ClearScreen();

    PixelScreenBuffer buffer(10, 10);
    std::vector<Pixel> bufferData = std::vector<Pixel>(10 * 10);
    for (int x = 0; x < 10; x++) {
        for (int y = 0; y < 10; y++) {
            bufferData[x + y * 10] = Pixel('#', RGB_Color(200, 100, 100));
        }
    }
    buffer.SetBufferData(bufferData);

    console.DrawBuffer(buffer);
}