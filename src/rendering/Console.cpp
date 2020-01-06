#include "Console.hpp"

namespace OpenCG::Rendering {
    Console::Console(int sizeX, int sizeY) {
        this->sizeX = sizeX;
        this->sizeY = sizeY;
    }

    void Console::ClearScreen() {
        std::cout << "\033[2J";
        std::cout << "\033[H";
    }

    void Console::SetCursorHome() {
        std::cout << "\033[H";
    }

    void Console::DrawBuffer(ScreenBuffer screenBuffer) {
        if (sizeX != screenBuffer.Width() || sizeY != screenBuffer.Height()) {
            throw "Pixel screen buffer does not fit the console window.";
        }

        for (int x = 0; x < sizeX; x++) {
            for (int y = 0; y < sizeX; y++) {
                RGB_Color pixelColor = screenBuffer.GetPixelColor(x, y);
                std::cout << "\033[38;2;" + std::to_string(pixelColor.Red()) + ";" + std::to_string(pixelColor.Green()) + ";" + std::to_string(pixelColor.Blue()) + "m" + "\u2588";
                std::cout << "\033[38;2;" + std::to_string(pixelColor.Red()) + ";" + std::to_string(pixelColor.Green()) + ";" + std::to_string(pixelColor.Blue()) + "m" + "\u2588";
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