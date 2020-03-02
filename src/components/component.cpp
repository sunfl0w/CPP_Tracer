#include "component.hpp"

namespace Tracer::Components {
    void Component::SetTag(std::string tag) {
        this->tag = tag;
    }

    std::string Component::GetTag() {
        return tag;
    }
}  // namespace Tracer::Components