#include "meshObject.hpp"

namespace Tracer::Objects {
    MeshObject::MeshObject(const glm::vec3& position, const Components::Material& material, const Components::Mesh& mesh) {
        this->transform = Components::Position::Transform(position, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        this->material = material;
        this->mesh = mesh;
    }

    Components::Position::Transform& MeshObject::GetTransform() {
        return transform;
    }

    Components::Material& MeshObject::GetMaterial() {
        return material;
    }

    Components::Mesh& MeshObject::GetMesh() {
        return mesh;
    }
}