#pragma once

#include <lib/glad/glad.h>

#include <fstream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <sstream>
#include <string>

namespace Tracer::Rendering {
    class Shader {
        unsigned int ID;

    public:
        Shader();

        Shader(std::string vertexShaderPath, std::string fragmentShaderPath);

        void Activate();

        unsigned int GetID();

        void SetInt(std::string name, int value);

        void SetVec4(std::string name, glm::vec4 vector);

        void SetMat4(std::string name, glm::mat4 matrix);
    };
}  // namespace Tracer::Rendering