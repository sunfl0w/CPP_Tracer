#pragma once

#include "object.hpp"
#include "component.hpp"
#include "vec3.hpp"
#include "transform.hpp"

namespace Tracer::Objects {
    class PointLight : public Object {
    private:
        float intensity;

    public:
        PointLight();
        
        PointLight(Math::Vec3 position, float intensity);
    };
}