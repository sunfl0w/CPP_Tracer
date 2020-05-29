#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "tris.hpp"

namespace Tracer::Components {
    class Mesh {
    private:
        std::vector<Math::Tris> data;

    public:
        Mesh();

        void LoadFromObjectFile(std::string filePath);

        std::vector<Math::Tris>& GetData();
    };
}  // namespace Tracer::Components