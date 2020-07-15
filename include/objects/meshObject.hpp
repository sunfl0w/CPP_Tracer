#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "renderableObject.hpp"
#include "mesh.hpp"

namespace Tracer::Objects {
    class MeshObject : public RenderableObject {
        Components::Mesh mesh;

    public:
        MeshObject(const glm::vec3& position, const Components::Material& material, const Components::Mesh& mesh);

        Components::Mesh& GetMesh();

        virtual Tracer::Math::IntersectionData Intersect(glm::vec3& origin, glm::vec3& dir);

        Tracer::Math::IntersectionData IntersectTris(Math::Tris& triangle, glm::vec3& origin, glm::vec3& dir) const;
    };
}  // namespace Tracer::Objects