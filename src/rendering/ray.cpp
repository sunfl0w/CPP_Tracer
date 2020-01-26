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
        //pvec.Normalize();
        float det = edge1.DotWith(pvec);

        //float epsilon = std::numeric_limits<float>::epsilon();
        float epsilon = 0.0001f;

        if(det < epsilon) {
            return IntersectData(Math::Vec3(0, 0, 0), RGB_Color(0, 0, 0), false);
        }

        float invDet = 1.0f / det;

        Math::Vec3 tvec = origin.SubtractOther(vertex0);

        float x = tvec.DotWith(pvec) * invDet;
        if(x < 0.0f || x > 1.0f) {
            return IntersectData(Math::Vec3(0, 0, 0), RGB_Color(0, 0, 0), false);
        }

        Math::Vec3 qvec = tvec.CrossWith(edge1);
        //qvec.Normalize();
        float y = direction.DotWith(qvec) * invDet;
        if(y < 0.0f || x + y > 1.0f) {
            return IntersectData(Math::Vec3(0, 0, 0), RGB_Color(0, 0, 0), false);
        }

        float z = edge2.DotWith(qvec) * invDet;

        float abs = std::abs(z);
        Math::Vec3 intersect = vertex0.AddOther(edge2.MultiplyWith(x).AddOther(edge1.MultiplyWith(y)));
        Math::Vec3 norm = edge1.CrossWith(edge2);
        norm = norm.MultiplyWith(0.01f);
        intersect = intersect.AddOther(norm);

        if(z < epsilon) {
            return IntersectData(Math::Vec3(0, 0, 0), RGB_Color(0, 0, 0), false);
        }

        return IntersectData(intersect, RGB_Color(100, 100, 100), true);
    }
}  // namespace OpenCG::Rendering