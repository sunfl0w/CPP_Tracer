#pragma once

#include <iostream>

#include "PixelScreenBuffer.hpp"

namespace OpenCG {
    class Console {
    private:
        int sizeX;
        int sizeY;
    public:
        Console(int sizeX, int sizeY);

        void ClearScreen();
        void SetCursorHome();
        void DrawBuffer(PixelScreenBuffer pixelScreenBuffer);
        int Width();
        int Height();
    };
}  // namespace OpneCG