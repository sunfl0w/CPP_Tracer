#include "renderableObject.hpp"

namespace Tracer::Objects {
    RenderableObject::RenderableObject(const Math::Vec3& position, const Components::Mesh& mesh, const Components::Material::Material& material) : transform(position), material(material) {
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