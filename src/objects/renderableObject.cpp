#include "renderableObject.hpp"

namespace Tracer::Objects {
    RenderableObject::RenderableObject(glm::vec3 position, Components::Mesh mesh, Components::Material::Material material) : material(material) {
        this->transform = Components::Position::Transform(position, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        this->mesh = mesh;
    }

    Components::Position::Transform& RenderableObject::GetTransform() {
        return transform;
    }

    Components::Mesh& RenderableObject::GetMesh() {
        return mesh;
    }

    Components::Material::Material& RenderableObject::GetMaterial() {
        return material;
    }
}