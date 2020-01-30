#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "tris.hpp"
#include "boundingBox.hpp"

namespace Tracer::Components {
    class Mesh {
    private:
        std::vector<Math::Tris> data;
        BoundingBox boundingBox;

    public:
        Mesh();

        void LoadFromObjectFile(std::string filePath);

        std::vector<Math::Tris>& GetData();

        bool RayIntersects(const Math::Ray& ray) const;
    };
}  // namespace Components