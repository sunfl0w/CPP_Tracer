#pragma once

#include "Vector2i.hpp"
#include "Direction.hpp"
#include <vector>

namespace SnakeGame {
    class Snake {
    private:
        std::vector<Vector2i> snakePartPositions; //First position in vector is the snakes head
        Direction movementDirection;
    public:
        Snake();
        void ChangeDirection(Direction direction);
    };
}  // namespace SnakeGame