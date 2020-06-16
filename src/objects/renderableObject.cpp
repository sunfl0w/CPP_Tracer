#include "renderableObject.hpp"

namespace Tracer::Objects {
    RenderableObject::RenderableObject(const glm::vec3& position, const Components::Mesh& mesh, const Components::Material& material) {
        this->transform = Components::Position::Transform(position, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        this->mesh = mesh;
        this->material = material;
    }

    Components::Position::Transform& RenderableObject::GetTransform() {
        return transform;
    }

    Components::Mesh& RenderableObject::GetMesh() {
        return mesh;
    }

    Components::Material& RenderableObject::GetMaterial() {
        return material;
    }
}