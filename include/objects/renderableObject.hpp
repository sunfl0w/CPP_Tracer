#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "material.hpp"
#include "mesh.hpp"
#include "transform.hpp"

namespace Tracer::Objects {
    class RenderableObject {
    private:
        Components::Position::Transform transform;
        Components::Mesh mesh;
        Components::Material::Material material;

    public:
        RenderableObject(glm::vec3 position, Components::Mesh mesh, Components::Material::Material material);

        Components::Position::Transform& GetTransform();

        Components::Mesh& GetMesh();

        Components::Material::Material& GetMaterial();
    };
}  // namespace Tracer::Objects