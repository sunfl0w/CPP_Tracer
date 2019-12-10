#pragma once

#include <vector>

#include "Pixel.hpp"

namespace OpenCG {
    class PixelScreenBuffer {
    private:
        int sizeX;
        int sizeY;
        std::vector<Pixel> bufferData;

    public:
        PixelScreenBuffer(int sizeX, int sizeY);

        int Width();
        int Height();
        std::vector<Pixel> GetBufferData();
        void SetBufferData(std::vector<Pixel> bufferData);
    };
}  // namespace OpenCG
