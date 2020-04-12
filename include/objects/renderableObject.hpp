#pragma once

#include "transform.hpp"
#include "mesh.hpp"
#include "material.hpp"
#include "vec3.hpp"

namespace Tracer::Objects {
    class RenderableObject {
    private:
        Components::Position::Transform transform;
        Components::Mesh mesh;
        Components::Material::Material material;

    public:
        RenderableObject(const Math::Vec3& position, const Components::Mesh& mesh, const Components::Material::Material& material);

        Components::Position::Transform& GetTransform();

        Components::Mesh& GetMesh();

        Components::Material::Material& GetMaterial();
    };
}