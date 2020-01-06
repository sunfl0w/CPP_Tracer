#include "vertex.hpp"

using namespace OpenCG::Math;

namespace OpenCG::Rendering {
    Vertex::Vertex(float x, float y, float z){
        point = OpenCG::Math::Vec3(x, y, z);
    }

    float Vertex::X() {
        return point.X();
    }

    float Vertex::Y() {
        return point.Y();
    }

    float Vertex::Z() {
        return point.Z();
    }

    Matrix Vertex::ToMatrix() {
        return Matrix(1, 4, std::vector<float>{X(), Y(), Z(), 1});
    }
}