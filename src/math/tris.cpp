#include "tris.hpp"

namespace Tracer::Math {
    Tris::Tris() {}

    Tris::Tris(glm::vec3& vert0, glm::vec3& vert1, glm::vec3& vert2) {
        this->vert0 = vert0;
        this->vert1 = vert1;
        this->vert2 = vert2;
    }

    const glm::vec3 Tris::GetNormal() {
        glm::vec3 normal = glm::cross(vert0 - vert1, vert0 - vert2);
        glm::normalize(normal);
        return normal;
    }
}  // namespace OpenCG::Renderer