#pragma once

#include <string>

namespace Tracer::Components {
    class Component {
        std::string tag;

    public:
        void SetTag(std::string tag);
        
        std::string GetTag();
    };
}  // namespace Tracer::Components