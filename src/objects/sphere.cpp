#include "sphere.hpp"

namespace Tracer::Objects {
    Sphere::Sphere(const glm::vec3& position, const Components::Material& material, float radius) : RenderableObject(position, material) {
        this->radius = radius;
    }

    float Sphere::GetRadius() {
        return radius;
    }

    Tracer::Math::IntersectionData Sphere::Intersect(glm::vec3& origin, glm::vec3& dir) const {
        glm::vec3 centerOrigin = transform.GetPosition() - origin;
        float tco = glm::dot(centerOrigin, dir);
        if (tco < 0) {
            return Tracer::Math::IntersectionData(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), material, false);
        }
        float dstToCenterSqr = glm::dot(centerOrigin, centerOrigin) - tco * tco;
        if(dstToCenterSqr > radius * radius) {
            return Tracer::Math::IntersectionData(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), material, false);
        }
        float thc = std::sqrt(radius * radius - dstToCenterSqr);
        float th0 = tco - thc;
        float th1 = tco + thc;
        if(th0 > th1) {
            std::swap(th0, th1);
        }
        if(th0 < 0) {
            th0 = th1;
            if(th0 < 0) {
                return Tracer::Math::IntersectionData(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), material, false);
            }
        }
        glm::vec3 hitPos = origin + th0 * dir;
        return Tracer::Math::IntersectionData(hitPos - transform.GetPosition(), hitPos, material, true);
    }
}  // namespace Tracer::Objects