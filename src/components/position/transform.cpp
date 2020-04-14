#include "transform.hpp"

namespace Tracer::Components::Position {
    Transform::Transform(const Vec3& position) {
        this->transformMatrix = Mat4();
        transformMatrix.ToIdentity();
        transformMatrix[3] = position.GetX();
        transformMatrix[7] = position.GetY();
        transformMatrix[11] = position.GetZ();
    }

    Vec3 Transform::GetPosition() {
        return Vec3(transformMatrix[3], transformMatrix[7], transformMatrix[11]);
    }

    void Transform::Translate(const Vec3& translation) {
        Mat4 translationMatrix = Mat4();
        translationMatrix.ToIdentity();
        translationMatrix[3] = translation.GetX();
        translationMatrix[7] = translation.GetY();
        translationMatrix[11] = translation.GetZ();
        transformMatrix = translationMatrix.MultiplyWith(transformMatrix);
    }

    void Transform::Rotate(float x, float y, float z) {
        float xRotationRad = x * M_PI / 180.0;
        float yRotationRad = y * M_PI / 180.0;
        float zRotationRad = z * M_PI / 180.0;

        Mat4 rotationMatrixY = Mat4();
        rotationMatrixY.ToIdentity();
        rotationMatrixY[0] = std::cos(yRotationRad);
        rotationMatrixY[2] = std::sin(yRotationRad);
        rotationMatrixY[8] = -std::sin(yRotationRad);
        rotationMatrixY[10] = std::cos(yRotationRad);

        transformMatrix = rotationMatrixY.MultiplyWith(transformMatrix);
    }

    Vec3 Transform::TransformPosition(const Vec3& position) {
        Vec4 result = transformMatrix.MultiplyWith(Vec4(position.GetX(), position.GetY(), position.GetZ(), 1));
        return Vec3(result.GetX(), result.GetY(), result.GetZ());
    }

    Tris Transform::TransformTris(const Tris& tris) {
        return Tris(TransformPosition(tris.GetV0()), TransformPosition(tris.GetV1()), TransformPosition(tris.GetV2()));
    }
}  // namespace Tracer::Components::Positioning