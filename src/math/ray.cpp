#include "ray.hpp"

namespace Tracer::Math {
    Ray::Ray(const Vec3& origin, const Math::Vec3& direction, int length) {
        this->origin = origin;
        this->direction = direction;
        this->length = length;
    }

    const Vec3& Ray::GetOrigin() const {
        return origin;
    }

    const Vec3& Ray::GetDirection() const {
        return direction;
    }

    int Ray::GetLength() const {
        return length;
    }

    IntersectionData Ray::Cast(const Tris& triangle) {
        //Möller–Trumbore intersection algorithm

        Math::Vec3 vertex0 = Math::Vec3(triangle.GetV0());
        Math::Vec3 vertex1 = Math::Vec3(triangle.GetV1());
        Math::Vec3 vertex2 = Math::Vec3(triangle.GetV2());

        Math::Vec3 edge1 = vertex1.Subtract(vertex0);
        Math::Vec3 edge2 = vertex2.Subtract(vertex0);

        Math::Vec3 pvec = direction.Cross(edge2);
        //pvec.Normalize();
        float det = edge1.Dot(pvec);

        //float epsilon = std::numeric_limits<float>::epsilon();
        float epsilon = 0.0001f;

        if (det < epsilon) {
            return IntersectionData(Math::Vec3(0, 0, 0), false);
        }

        float invDet = 1.0f / det;

        Math::Vec3 tvec = origin.Subtract(vertex0);

        float x = tvec.Dot(pvec) * invDet;
        if (x < 0.0f || x > 1.0f) {
            return IntersectionData(Math::Vec3(0, 0, 0), false);
        }

        Math::Vec3 qvec = tvec.Cross(edge1);
        //qvec.Normalize();
        float y = direction.Dot(qvec) * invDet;
        if (y < 0.0f || x + y > 1.0f) {
            return IntersectionData(Math::Vec3(0, 0, 0), false);
        }

        float z = edge2.Dot(qvec) * invDet;

        Math::Vec3 intersect = vertex0.Add(edge2.Multiply(x).Add(edge1.Multiply(y)));
        Math::Vec3 norm = edge1.Cross(edge2);
        norm = norm.Multiply(0.005f);
        intersect = intersect.Add(norm);

        if (z < epsilon) {
            return IntersectionData(Math::Vec3(0, 0, 0), false);
        }

        return IntersectionData(intersect, true);
    }
}  // namespace OpenCG::Rendering