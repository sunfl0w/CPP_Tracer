#include "transform.hpp"

namespace Tracer::Components::Position {
    Transform::Transform(const Vec3& position) {
        this->position = position;
    }

    Vec3 Transform::GetPosition() {
        return position;
    }

    void Transform::Translate(const Vec3& translation) {
        //Vec3 temp = position.Add(translation);
        position = position.Add(translation);
    }

    void Transform::Rotate(float x, float y, float z) {
        rotation = rotation.Add(Vec3(x, y, z));
    }
}  // namespace Tracer::Components::Positioning