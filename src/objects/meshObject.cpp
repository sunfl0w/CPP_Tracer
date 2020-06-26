#include "meshObject.hpp"

namespace Tracer::Objects {
    MeshObject::MeshObject(const glm::vec3& position, const Components::Material& material, const Components::Mesh& mesh) : RenderableObject(position, material) {
        this->mesh = mesh;
    }

    Components::Mesh& MeshObject::GetMesh() {
        return mesh;
    }

    IntersectionData MeshObject::Intersect(glm::vec3& origin, glm::vec3& dir) const {

    }
}