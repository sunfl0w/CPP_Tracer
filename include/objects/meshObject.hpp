#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "material.hpp"
#include "mesh.hpp"
#include "transform.hpp"

namespace Tracer::Objects {
    class MeshObject {
        Components::Position::Transform transform;
        Components::Material material;
        Components::Mesh mesh;

    public:
        MeshObject(const glm::vec3& position, const Components::Material& material, const Components::Mesh& mesh);

        Components::Position::Transform& GetTransform();

        Components::Material& GetMaterial();

        Components::Mesh& GetMesh();
    };
}  // namespace Tracer::Objects