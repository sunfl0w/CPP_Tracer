#include "ray.hpp"

namespace OpenCG::Rendering {
    Ray::Ray(Math::Vec3 origin, Math::Vec3 direction, int length) {
        this->origin = origin;
        this->direction = direction;
        this->length = length;
    }

    IntersectData Ray::Cast(Tris triangle) {
        //Möller–Trumbore intersection algorithm
        
        const float EPSILON = 0.0000001;
        Math::Vec3 vertex0 = triangle.V1().data;
        Math::Vec3 vertex1 = triangle.V2().data;
        Math::Vec3 vertex2 = triangle.V3().data;
        Math::Vec3 edge1, edge2, h, s, q;
        float a, f, u, v;
        edge1 = vertex1.SubtractOther(vertex0);
        edge2 = vertex2.SubtractOther(vertex0);
        h = direction.CrossWith(edge2);
        a = edge1.DotWith(h);
        if (a > -EPSILON && a < EPSILON)
            return IntersectData(Math::Vec3(0, 0, 0), RGB_Color(0, 0, 0));  // This ray is parallel to this triangle.
        f = 1.0 / a;
        s = origin.SubtractOther(vertex0);
        u = f * s.DotWith(h);
        if (u < 0.0 || u > 1.0)
            return IntersectData(Math::Vec3(0, 0, 0), RGB_Color(0, 0, 0));
        q = s.CrossWith(edge1);
        v = f * direction.DotWith(q);
        if (v < 0.0 || u + v > 1.0)
            return IntersectData(Math::Vec3(0, 0, 0), RGB_Color(0, 0, 0));
        // At this stage we can compute t to find out where the intersection point is on the line.
        float t = f * edge2.DotWith(q);
        if (t > EPSILON && t < 1 - EPSILON)  // ray intersection
        {
            Math::Vec3 intersectionPoint = origin.AddOther(direction).MultiplyWith(t);
            return IntersectData(intersectionPoint, RGB_Color(200, 100, 50));
        } else  // This means that there is a line intersection but not a ray intersection.
            return IntersectData(Math::Vec3(0, 0, 0), RGB_Color(0, 0, 0));
    }
}  // namespace OpenCG::Rendering