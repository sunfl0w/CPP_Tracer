#include "camera.hpp"

namespace OpenCG::Rendering {
    Camera::Camera(const Math::Vec3& camPos, const Math::Vec3& target, const Math::Vec3& up) {
        Math::Vec3 zAxis = camPos.SubtractOther(target);
        zAxis.Normalize();
        Math::Vec3 xAxis = up.CrossWith(zAxis);
        xAxis.Normalize();
        Math::Vec3 yAxis = zAxis.CrossWith(xAxis);

        viewMatrix = Math::Matrix(4, 4, std::vector<float>{xAxis.X(), yAxis.X(), zAxis.X(), 0, xAxis.Y(), yAxis.Y(), zAxis.Y(), 0, xAxis.Z(), yAxis.Z(), zAxis.Z(), 0, -xAxis.MultiplyWith(camPos), -yAxis.MultiplyWith(camPos), -zAxis.MultiplyWith(camPos), 1});
    }

    Math::Matrix Camera::GetMatrix() {
        return viewMatrix;
    }
}  // namespace OpenCG::Renderer