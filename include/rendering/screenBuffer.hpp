#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "rgb_Color.hpp"

namespace Tracer::Rendering {
    class ScreenBuffer {
    private:
        int sizeX;
        int sizeY;
        std::vector<sf::Uint8> bufferData;

    public:
        ScreenBuffer(int sizeX, int sizeY);

        int Width();
        int Height();
        sf::Uint8* GetBufferData();
        void SetBufferData(std::vector<sf::Uint8> bufferData);
        void SetPixelColor(int x, int y, Components::Color::RGB_Color color);
        void Draw();
    };
}  // namespace Tracer::Rendering
