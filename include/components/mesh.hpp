#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "tris.hpp"

using namespace OpenCG::Rendering;

namespace OpenCG::Components {
    class Mesh {
    private:
        std::vector<Tris> data;
    public:
        float minX, maxX, minY, maxY, minZ, maxZ;
        Mesh();
        void LoadFromObjectFile(std::string filePath);
        std::vector<Tris> GetData();
    };
}  // namespace Components