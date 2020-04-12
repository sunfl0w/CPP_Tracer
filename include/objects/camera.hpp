#pragma once

#include "object.hpp"
#include "component.hpp"
#include "vec3.hpp"
#include "transform.hpp"

namespace Tracer::Objects {
    class Camera : public Object {
    private:

    public:
        Camera();
        
        Camera(Math::Vec3 position, Math::Vec3 direction);
    };
}  // namespace Tracer::Objects