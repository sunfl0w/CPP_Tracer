#include "object.hpp"

namespace Tracer::Objects {
    Object::Object(std::string tag) {
        this->tag = tag;
        this->components = std::vector<std::unique_ptr<Components::Component>>();
    }

    Object::Object(const Object& object) {
        tag = object.tag;
        for(int i = 0; i < object.components.size(); i++) {
            components.push_back(std::unique_ptr<Components::Component>(new Components::Component(*object.components[i])));
        }
    }

    std::string Object::GetTag() {
        return tag;
    }

    void Object::SetTag(std::string tag) {
        this->tag = tag;
    }

    void Object::AddComponent(const Components::Component& component) {
        bool isTagPresent = false;
        for(int i = 0; i < components.size(); i++) {
            if(components[i]->GetTag() == component.GetTag()) {
                return;
            }
        }
        components.push_back(std::unique_ptr<Components::Component>(new Components::Component(component)));
    }

    std::unique_ptr<Components::Component> Object::GetComponent(std::string tag) {
        for(int i = 0; i < components.size(); i++) {
            if(components[i]->GetTag() == tag) {
                return std::unique_ptr<Components::Component>(new Components::Component(*components[i]));
            }
        }
        return nullptr;
    }

    void Object::RemoveComponent(std::string tag) {
        for(int i = 0; i < components.size(); i++) {
            if(components[i]->GetTag() == tag) {
                components.erase(components.begin() + i);
                break;
            }
        }
    }
}