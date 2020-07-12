#include "meshObject.hpp"

namespace Tracer::Objects {
    MeshObject::MeshObject(const glm::vec3& position, const Components::Material& material, const Components::Mesh& mesh) : RenderableObject(position, material) {
        this->mesh = mesh;
    }

    Components::Mesh& MeshObject::GetMesh() {
        return mesh;
    }

    Tracer::Math::IntersectionData MeshObject::Intersect(glm::vec3& origin, glm::vec3& dir) {
        Tracer::Math::IntersectionData closestIntersect = Math::IntersectionData();
        float closesIntersectDst = 999999.9f;
        for (Math::Tris triangle : mesh.GetData()) {
            //Would be way faster on the GPU but we want to use the CPU exclusively
            Math::Tris transformedTriangle;
            transformedTriangle.vert0 = transform.GetTransformMatrix() * glm::vec4(triangle.vert0, 1.0f);
            transformedTriangle.vert1 = transform.GetTransformMatrix() * glm::vec4(triangle.vert1, 1.0f);
            transformedTriangle.vert2 = transform.GetTransformMatrix() * glm::vec4(triangle.vert2, 1.0f);

            Tracer::Math::IntersectionData intersect = IntersectTris(transformedTriangle, origin, dir);
            float dst = glm::distance(intersect.GetIntersectionPos(), origin);
            if (intersect.IsHit() && dst < closesIntersectDst) {
                closesIntersectDst = dst;
                closestIntersect = intersect;
            }
        }
        return closestIntersect;
    }

    Tracer::Math::IntersectionData MeshObject::IntersectTris(Math::Tris& triangle, glm::vec3& origin, glm::vec3& dir) const {
        //Möller–Trumbore intersection algorithm
        glm::vec3 vertex0 = triangle.vert0;
        glm::vec3 vertex1 = triangle.vert1;
        glm::vec3 vertex2 = triangle.vert2;

        glm::vec3 edge1 = vertex1 - vertex0;
        glm::vec3 edge2 = vertex2 - vertex0;

        glm::vec3 pvec = glm::cross(dir, edge2);
        //pvec.Normalize();
        float det = glm::dot(edge1, pvec);

        float epsilon = 0.00001f;

        //Culling stuff. Don't touch for now

        /*if (det < epsilon) {
            return IntersectionData(triangle, glm::vec3(0, 0, 0), false);
        }*/
        //Culling

        if (std::fabs(det) < epsilon) {
            return Tracer::Math::IntersectionData(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), material, false);
        }

        float invDet = 1.0f / det;

        glm::vec3 tvec = origin - vertex0;

        float x = glm::dot(tvec, pvec) * invDet;
        if (x < 0.0f || x > 1.0f) {
            return Tracer::Math::IntersectionData(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), material, false);
        }

        glm::vec3 qvec = glm::cross(tvec, edge1);
        float y = glm::dot(dir, qvec) * invDet;
        if (y < 0.0f || x + y > 1.0f) {
            return Tracer::Math::IntersectionData(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), material, false);
        }

        float z = glm::dot(edge2, qvec) * invDet;

        glm::vec3 intersect = origin + dir * z;

        if (z < epsilon) {
            return Tracer::Math::IntersectionData(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), material, false);
        }

        return Tracer::Math::IntersectionData(triangle.GetNormal(), intersect, material, true);
    }
}  // namespace Tracer::Objects