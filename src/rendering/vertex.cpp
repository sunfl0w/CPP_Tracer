#include "vertex.hpp"

using namespace OpenCG::Math;

namespace OpenCG::Rendering {
    Vertex::Vertex() {}

    Vertex::Vertex(float x, float y, float z) {
        data = OpenCG::Math::Vec3(x, y, z);
    }

    float Vertex::X() {
        return data.X();
    }

    float Vertex::Y() {
        return data.Y();
    }

    float Vertex::Z() {
        return data.Z();
    }

    void Vertex::Set(int index, float value) {
        data.Set(index, value);
    }
}  // namespace OpenCG::Rendering