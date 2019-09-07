#pragma once

#include "PixelScreenBuffer.hpp"

class Console {
   public:
    Console(int sizeX, int sizeY);

    void ClearScreen();
    void DrawBuffer(PixelScreenBuffer pixelScreenBuffer);
};