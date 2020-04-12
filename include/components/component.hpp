#pragma once

#include <string>

namespace Tracer::Components {
    class Component {
        std::string tag;

    public:
    Component(std::string tag);

    void SetTag(std::string tag);
        
    std::string GetTag() const;
    };
}  // namespace Tracer::Components