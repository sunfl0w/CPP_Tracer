#include "transform.hpp"

namespace Tracer::Components::Positioning {
    Transform::Transform(const Vec3& position) {
        transformMatrix.ToIdentity();
    }

    void Transform::Translate(const Vec3& translation) {
        Mat4 translationMatrix = Mat4();
        translationMatrix.ToIdentity();
        translationMatrix[3] = translation.GetX();
        translationMatrix[7] = translation.GetY();
        translationMatrix[11] = translation.GetZ();

        transformMatrix = transformMatrix.MultiplyWith(transformMatrix);
    }
}  // namespace Tracer::Components::Positioning