#include "screenBuffer.hpp"

namespace Tracer::Rendering {
    ScreenBuffer::ScreenBuffer(int sizeX, int sizeY) {
        this->sizeX = sizeX;
        this->sizeY = sizeY;
        bufferData = std::vector<sf::Uint8>(sizeX * sizeY * 4);
    }

    int ScreenBuffer::Width() {
        return sizeX;
    }
    int ScreenBuffer::Height() {
        return sizeY;
    }

    sf::Uint8* ScreenBuffer::GetBufferData() {
        return bufferData.data();
    }

    void ScreenBuffer::SetBufferData(std::vector<sf::Uint8> bufferData) {
        this->bufferData = bufferData;
    }

    void ScreenBuffer::SetPixelColor(int x, int y, RGB_Color color) {
        bufferData[(x + sizeX * y) * 4] = color.r;
        bufferData[(x + sizeX * y) * 4 + 1] = color.g;
        bufferData[(x + sizeX * y) * 4 + 2] = color.b;
        bufferData[(x + sizeX * y) * 4 + 3] = 255;
    }

    void ScreenBuffer::Draw() {

    }
}  // namespace OpenCG