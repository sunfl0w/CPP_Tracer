#include "vertex.hpp"

namespace OpenCG::Renderer {
    Vertex::Vertex(float x, float y, float z){
        point = OpenCG::Math::Vec3(x, y, z);
    }
}