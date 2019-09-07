#pragma once

#include "Snake.hpp"
#include "Field.hpp"

#include "PixelScreenBuffer.hpp"

#include <vector>

namespace SnakeGame {
    class Board {
    private:
        Snake snake;
        std::vector<Field> fields;
    public:;
        Board();
        Field* GetField(int xPos, int yPos);
        Field* GetField(Vector2i* position);
        PixelScreenBuffer ToPixelScreenBuffer();
    };
}  // namespace SnakeGame