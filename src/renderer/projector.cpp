#include "projector.hpp"

namespace OpenCG::Renderer {
    Projector::Projector(int width, int height, int near, int far) {
        projection = Math::Matrix(4, 4, std::vector<float>{2.0f / width, 0, 0, 0, 0, 2.0f / height, 0, 0, 0, 0, 1.0f / (near - far), -1, 0, 0, near / (float)(near - far), 0});
    }

    Math::Matrix Projector::GetMatrix() {
        return projection;
    }
}  // namespace OpenCG::Renderer