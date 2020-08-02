#pragma once

#include <lib/glad/glad.h>
#include <stb_image.h>

#include <iostream>
#include <string>

namespace Tracer::Rendering::Text {
    class BitmapFont {
    private:
        unsigned int bitmapID;
        unsigned int characterSize;

    public:
        BitmapFont(std::string bitmapPath, unsigned int characterSize);

        void Activate() const;
        unsigned int GetID() const;
    };
}  // namespace Tracer::Rendering::Text