#pragma once

#include <iostream>

#include "screenBuffer.hpp"

namespace OpenCG::Rendering {
    class Console {
    private:
        int sizeX;
        int sizeY;
    public:
        Console(int sizeX, int sizeY);

        void ClearScreen();
        void SetCursorHome();
        void DrawBuffer(ScreenBuffer pixelScreenBuffer);
        int Width();
        int Height();
    };
}  // namespace OpneCG