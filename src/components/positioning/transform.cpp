#include "transform.hpp"

namespace Tracer::Components::Positioning {
    Transform::Transform(const Vec3& position) : Component("TransformComponent") {
        transformMatrix.ToIdentity();
    }

    Vec3 Transform::GetPosition() {
        return Vec3(transformMatrix[3], transformMatrix[7], transformMatrix[11]);
    }

    void Transform::Translate(const Vec3& translation) {
        Mat4 translationMatrix = Mat4();
        translationMatrix[0] = 1;
        translationMatrix[3] = translation.GetX();
        translationMatrix[5] = 1;
        translationMatrix[7] = translation.GetY();
        translationMatrix[10] = 1;
        translationMatrix[11] = translation.GetZ();
        translationMatrix[15] = 1;

        transformMatrix = translationMatrix.MultiplyWith(transformMatrix);
    }

    void Transform::Rotate(float x, float y, float z) {
        float xRotationRad = x * M_PI / 180.0;
        float yRotationRad = y * M_PI / 180.0;
        float zRotationRad = z * M_PI / 180.0;

        Mat4 rotationMatrixX = Mat4();
        rotationMatrixX[0] = 1;
        rotationMatrixX[5] = std::cos(xRotationRad);
        rotationMatrixX[6] = -std::sin(xRotationRad);
        rotationMatrixX[9] = std::sin(xRotationRad);
        rotationMatrixX[10] = std::cos(xRotationRad);
        rotationMatrixX[15] = 1;

        Mat4 rotationMatrixY = Mat4();
        rotationMatrixY[0] = std::cos(yRotationRad);
        rotationMatrixY[2] = std::sin(yRotationRad);
        rotationMatrixY[5] = 1;
        rotationMatrixY[8] = -std::sin(yRotationRad);
        rotationMatrixY[10] = std::cos(yRotationRad);
        rotationMatrixY[15] = 1;

        Mat4 rotationMatrixZ = Mat4();
        rotationMatrixZ[0] = std::cos(zRotationRad);
        rotationMatrixZ[1] = -std::sin(zRotationRad);
        rotationMatrixZ[4] = std::sin(zRotationRad);
        rotationMatrixZ[5] = std::cos(zRotationRad);
        rotationMatrixZ[10] = 1;
        rotationMatrixZ[15] = 1;

        transformMatrix = rotationMatrixX.MultiplyWith(transformMatrix);
        transformMatrix = rotationMatrixY.MultiplyWith(transformMatrix);
        transformMatrix = rotationMatrixZ.MultiplyWith(transformMatrix);
    }
}  // namespace Tracer::Components::Positioning