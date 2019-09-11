#include <iostream>
#include <string.h>

int main(int, char**) {
    for (int r = 0; r < 256; r+= 16) {
        for (int g = 0; g < 256; g+= 16) {
            for (int b = 0; b < 256; b+= 16) {
                std::string colorString = "\033[38;2;" + std::to_string(r) + ";" + std::to_string(g) + ";" + std::to_string(b) + "m#";
                std::cout << colorString;
            }
        }
    }
    //std::cout << "\033[38;5;4;176;2mHello";
    //std::cout << "Hello, world!\n";
}