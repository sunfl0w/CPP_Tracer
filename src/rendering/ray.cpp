#include "ray.hpp"

namespace OpenCG::Rendering {
    Ray::Ray(Math::Vec3 origin, Math::Vec3 direction, int length) {
        this->origin = origin;
        this->direction = direction;
        this->length = length;
    }

    IntersectData Ray::Cast(Tris triangle) {
        //Möller–Trumbore intersection algorithm
        
        Math::Vec3 vertex0 = triangle.V1().data;
        Math::Vec3 vertex1 = triangle.V2().data;
        Math::Vec3 vertex2 = triangle.V3().data;

        Math::Vec3 edge1 = vertex1.SubtractOther(vertex0);
        Math::Vec3 edge2 = vertex2.SubtractOther(vertex0);
        
        Math::Vec3 pvec = direction.CrossWith(edge2);
        float det = edge1.DotWith(pvec);

        //float epsilon = std::numeric_limits<float>::epsilon();
        float epsilon = 0.000000000001f;

        if(det > epsilon && det < epsilon) {
            return IntersectData(Math::Vec3(0, 0, 0), RGB_Color(0, 0, 0), false, 0.0f);
        }

        float invDet = 1.0f / det;

        Math::Vec3 tvec = origin.SubtractOther(vertex0);

        float x = tvec.DotWith(pvec) * invDet;
        if(x < 0.0f || x > 1.0f) {
            return IntersectData(Math::Vec3(0, 0, 0), RGB_Color(0, 0, 0), false, 0.0f);
        }

        Math::Vec3 qvec = tvec.CrossWith(edge1);
        float y = direction.DotWith(qvec) * invDet;
        if(y < 0.0f || x + y > 1.0f) {
            return IntersectData(Math::Vec3(0, 0, 0), RGB_Color(0, 0, 0), false, 0.0f);
        }

        float z = edge2.DotWith(qvec) * invDet;

        float abs = std::abs(z);
        float dst = std::abs(origin.DistanceTo(direction));
        Math::Vec3 intersect = vertex0.AddOther(edge2.MultiplyWith(x).AddOther(edge1.MultiplyWith(y)));

        if(z < epsilon) {
            return IntersectData(Math::Vec3(0, 0, 0), RGB_Color(0, 0, 0), false, 0.0f);
        }

        return IntersectData(intersect, RGB_Color(100, 100, 100), true, dst);
    }
}  // namespace OpenCG::Rendering