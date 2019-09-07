#pragma once

#include "Pixel.hpp"

#include <vector>

class PixelScreenBuffer {
private:
    std::vector<Pixel> bufferData;
public:
    PixelScreenBuffer(int sizeX, int sizeY);
};
