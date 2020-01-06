#pragma once

#include <vector>

#include "RGB_Color.hpp"

namespace OpenCG::Rendering {
    class ScreenBuffer {
    private:
        int sizeX;
        int sizeY;
        std::vector<RGB_Color> bufferData;

    public:
        ScreenBuffer(int sizeX, int sizeY);

        int Width();
        int Height();
        std::vector<RGB_Color> GetBufferData();
        void SetBufferData(std::vector<RGB_Color> bufferData);
        RGB_Color GetPixelColor(int x, int y);
        void SetPixelColor(int x, int y, RGB_Color color);
        void Draw();
    };
}  // namespace OpenCG
