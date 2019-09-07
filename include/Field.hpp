#pragma once

#include "FieldType.hpp"

namespace SnakeGame {
    class Field {
    public:
        FieldType fieldType;
        Field(FieldType fieldType);
    };
}  // namespace SnakeGame