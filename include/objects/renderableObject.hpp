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
        Components::Material material;

    public:
        RenderableObject(const glm::vec3& position, const Components::Mesh& mesh, const Components::Material& material);

        Components::Position::Transform& GetTransform();

        Components::Mesh& GetMesh();

        Components::Material& GetMaterial();
    };
}  // namespace Tracer::Objects