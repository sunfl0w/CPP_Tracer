#pragma once

#include <string>
#include <glm/glm.hpp>

#include "bitmapFont.hpp"
#include "shader.hpp"

namespace Tracer::Rendering::Text {
    class BitmapTextRenderer {
    private:
        BitmapFont bitmapFont;
        Shader textShader;
        unsigned int VAO;

    public:
        BitmapTextRenderer(BitmapFont bitmapFont);

        void DrawText(std::string text, glm::vec2 position, glm::vec2 size) const;
    };
}  // namespace Tracer::Rendering::Text