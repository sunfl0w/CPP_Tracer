#include "component.hpp"

namespace Tracer::Components {
    Component::Component(std::string tag) {
        this->tag = tag;
    }

    void Component::SetTag(std::string tag) {
        this->tag = tag;
    }

    std::string Component::GetTag() const {
        return tag;
    }
}  // namespace Tracer::Components