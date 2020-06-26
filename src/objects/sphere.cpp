#include "sphere.hpp"

namespace Tracer::Objects {
    Sphere::Sphere(const glm::vec3& position, const Components::Material& material, float radius) : RenderableObject(position, material) {
        this->radius = radius;
    }

    const glm::vec3& Sphere::GetCenter() {
        return transform.GetPosition();
    }

    float Sphere::GetRadius() {
        return radius;
    }

    IntersectionData Sphere::Intersect(glm::vec3& origin, glm::vec3& dir) const {

    }
}  // namespace Tracer::Objects