#include "screenBuffer.hpp"

namespace OpenCG::Rendering {
    ScreenBuffer::ScreenBuffer(int sizeX, int sizeY) {
        this->sizeX = sizeX;
        this->sizeY = sizeY;
        bufferData = std::vector<RGB_Color>(sizeX * sizeY);
    }

    int ScreenBuffer::Width() {
        return sizeX;
    }
    int ScreenBuffer::Height() {
        return sizeY;
    }

    std::vector<RGB_Color> ScreenBuffer::GetBufferData() {
        return bufferData;
    }

    void ScreenBuffer::SetBufferData(std::vector<RGB_Color> bufferData) {
        this->bufferData = bufferData;
    }

    RGB_Color ScreenBuffer::GetPixelColor(int x, int y) {
        return bufferData[x + sizeX * y];
    }

    void ScreenBuffer::SetPixelColor(int x, int y, RGB_Color color) {
        bufferData[x + sizeX * y] = color;
    }

    void ScreenBuffer::Draw() {

    }
}  // namespace OpenCG