#pragma once

#include <array>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "vec3.hpp"

namespace Tracer::Math {
    class Tris {
    public:
        glm::vec3 vert0;
        glm::vec3 vert1;
        glm::vec3 vert2;


        Tris();

        Tris(glm::vec3& vert0, glm::vec3& vert1, glm::vec3& vert2);

        const glm::vec3 GetNormal();
    };
}  // namespace Tracer::Math