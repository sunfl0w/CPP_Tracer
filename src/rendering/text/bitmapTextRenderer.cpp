#include "bitmapTextRenderer.hpp"

namespace Tracer::Rendering::Text {
    BitmapTextRenderer::BitmapTextRenderer(BitmapFont bitmapFont) {
        this->bitmapFont = bitmapFont;
        textShader = Shader("bitmapFont.vs", GL_VERTEX_SHADER, "bitmapFont.fs", GL_FRAGMENT_SHADER);

        unsigned int VBO, EBO;
        float positions[] = {
            1.0f, 1.0f,
            1.0f, 0.0f,
            0.0f, 0.0f,
            0.0f, 1.0f};

        unsigned int indices[] = {
            0, 1, 3,
            1, 2, 3};

        glGenVertexArrays(1, &this->VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(this->VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glBindVertexArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    void BitmapTextRenderer::DrawText(std::string text, glm::vec2 position, glm::vec2 size) const {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(position, 0.0f));
        model = glm::scale(model, glm::vec3(size, 1.0f));

        textShader.Activate();
        textShader.SetVec2("texCoord", color);
        textShader.SetMat4("model", model);

        glActiveTexture(GL_TEXTURE0);
        bitmapFont.Activate();

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }
}  // namespace Tracer::Rendering::Text