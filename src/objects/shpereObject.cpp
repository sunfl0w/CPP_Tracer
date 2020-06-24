#include "sphereObject.hpp"

namespace Tracer::Objects {
    SphereObject::SphereObject(const glm::vec3& position, const Components::Material& material, float radius) {
        this->transform = Components::Position::Transform(position, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        this->material = material;
        this->radius = radius;
    }

    Components::Position::Transform& SphereObject::GetTransform() {
        return transform;
    }

    Components::Material& SphereObject::GetMaterial() {
        return material;
    }

    const glm::vec3& SphereObject::GetCenter() {
        return transform.GetPosition();
    }

    float SphereObject::GetRadius() {
        return radius;
    }
}  // namespace Tracer::Objects