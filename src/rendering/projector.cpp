#include "projector.hpp"

namespace OpenCG::Rendering {
    Projector::Projector() {
        projection = Math::Matrix(1, 1, std::vector<float>{1.0f});
    }
    Projector::Projector(int fov, int near, int far) {
        float height = 1 / std::tan(((fov / 2.0f) * M_PI ) / 180);
        float width = height;
        projection = Math::Matrix(4, 4, std::vector<float>{width, 0, 0, 0, 0, height, 0, 0, 0, 0, far / (float)(far - near), 1, 0, 0, (near * far) / (float)(near - far), 0});
    }

    Math::Matrix Projector::GetMatrix() {
        return projection;
    }
}  // namespace OpenCG::Renderer