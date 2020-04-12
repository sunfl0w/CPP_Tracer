#include "boundingBox.hpp"

namespace Tracer::Components {
    BoundingBox::BoundingBox() : Component("BoundingBoxComponent") {}

    BoundingBox::BoundingBox(const std::vector<Math::Tris>& meshData) : Component("BoundingBoxComponent") {
        for (Math::Tris triangle : meshData) {
            for (Math::Vec3 vertex : triangle.GetVertecies()) {
                if (vertex.GetX() < minX) {
                    minX = vertex.GetX();
                }
                if (vertex.GetY() < minY) {
                    minY = vertex.GetY();
                }
                if (vertex.GetZ() < minZ) {
                    minZ = vertex.GetZ();
                }

                if (vertex.GetX() > maxX) {
                    maxX = vertex.GetX();
                }
                if (vertex.GetY() > maxY) {
                    maxY = vertex.GetY();
                }
                if (vertex.GetZ() > maxZ) {
                    maxZ = vertex.GetZ();
                }
            }
        }
    }

    bool BoundingBox::RayIntersects(const Math::Ray& ray) const {
        Math::Vec3 invDir = Math::Vec3(ray.GetDirection());
        invDir = invDir.Multiply(-1.0f);
        float tmin = 0.0f;
        float tmax = 0.0f;
        float tymin = 0.0f;
        float tymax = 0.0f;
        float tzmin = 0.0f;
        float tzmax = 0.0f;

        if (ray.GetDirection().GetX() >= 0) {
            tmin = (minX - ray.GetOrigin().GetX()) / ray.GetDirection().GetX();
            tmax = (maxX - ray.GetOrigin().GetX()) / ray.GetDirection().GetX();
        } else {
            tmin = (maxX - ray.GetOrigin().GetX()) / ray.GetDirection().GetX();
            tmax = (minX - ray.GetOrigin().GetX()) / ray.GetDirection().GetX();
        }
        if (ray.GetDirection().GetY() >= 0) {
            tymin = (minY - ray.GetOrigin().GetY()) / ray.GetDirection().GetY();
            tymax = (maxY - ray.GetOrigin().GetY()) / ray.GetDirection().GetY();
        } else {
            tymin = (maxY - ray.GetOrigin().GetY()) / ray.GetDirection().GetY();
            tymax = (minY - ray.GetOrigin().GetY()) / ray.GetDirection().GetY();
        }
        if ((tmin > tymax) || (tymin > tmax)) {
            return false;
        }
        if (tymin > tmin) {
            tmin = tymin;
        }
        if (tymax < tmax) {
            tmax = tymax;
        }
        if (ray.GetDirection().GetZ() >= 0) {
            tzmin = (minZ - ray.GetOrigin().GetZ()) / ray.GetDirection().GetZ();
            tzmax = (maxZ - ray.GetOrigin().GetZ()) / ray.GetDirection().GetZ();
        } else {
            tzmin = (maxZ - ray.GetOrigin().GetZ()) / ray.GetDirection().GetZ();
            tzmax = (minZ - ray.GetOrigin().GetZ()) / ray.GetDirection().GetZ();
        }
        if ((tmin > tzmax) || (tzmin > tmax)) {
            return false;
        }
        return true;
    }
}  // namespace Tracer::Components