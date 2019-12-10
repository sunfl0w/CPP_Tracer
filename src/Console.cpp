#include "Console.hpp"

namespace OpenCG {
    Console::Console(int sizeX, int sizeY) {
        this->sizeX = sizeX;
        this->sizeY = sizeY;
    }

    void Console::ClearScreen() {
        std::cout << "\033[2J\033[H";
    }

    void Console::SetCursorHome() {
        std::cout << "\033[H";
    }

    void Console::DrawBuffer(PixelScreenBuffer pixelScreenBuffer) {
        if (sizeX != pixelScreenBuffer.Width() || sizeY != pixelScreenBuffer.Height()) {
            throw "Pixel screen buffer does not fit the console window.";
        }

        for (int x = 0; x < sizeX; x++) {
            for (int y = 0; y < sizeX; y++) {
                Pixel pixel = pixelScreenBuffer.GetBufferData()[pixelScreenBuffer.Width() * y + x];
                std::cout << "\033[38;2;" + std::to_string(pixel.GetColor().Red()) + ";" + std::to_string(pixel.GetColor().Green()) + ";" + std::to_string(pixel.GetColor().Blue()) + "m" + pixel.GetCharacter();
                std::cout << "\033[38;2;" + std::to_string(pixel.GetColor().Red()) + ";" + std::to_string(pixel.GetColor().Green()) + ";" + std::to_string(pixel.GetColor().Blue()) + "m" + pixel.GetCharacter();
            }
            std::cout << "\n";
        }
    }

    int Console::Width() {
        return sizeX;
    }

    int Console::Height() {
        return sizeY;
    }
}  // namespace OpenCG