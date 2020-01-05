#include "PixelScreenBuffer.hpp"

namespace OpenCG {
    PixelScreenBuffer::PixelScreenBuffer(int sizeX, int sizeY) {
        this->sizeX = sizeX;
        this->sizeY = sizeY;
        bufferData = std::vector<Pixel>(sizeX * sizeY);
    }

    int PixelScreenBuffer::Width() {
        return sizeX;
    }
    int PixelScreenBuffer::Height() {
        return sizeY;
    }

    std::vector<Pixel> PixelScreenBuffer::GetBufferData() {
        return bufferData;
    }

    void PixelScreenBuffer::SetBufferData(std::vector<Pixel> bufferData) {
        this->bufferData = bufferData;
    }
}  // namespace OpenCG