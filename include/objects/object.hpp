#pragma once

#include <memory>
#include <string>
#include <vector>
#include <algorithm>

#include "component.hpp"

namespace Tracer::Objects {
    class Object {
    protected:
        std::string tag = "";
        std::vector<std::unique_ptr<Components::Component>> components;

    public:
        Object(std::string tag);

        Object(const Object& object);

        std::string GetTag();

        void SetTag(std::string tag);

        void AddComponent(const Components::Component& component);

        std::unique_ptr<Components::Component> GetComponent(std::string tag);

        void RemoveComponent(std::string tag);
    };
}  // namespace Tracer::Objects