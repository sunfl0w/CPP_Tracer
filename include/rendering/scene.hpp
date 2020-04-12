#pragma once

#include <memory>
#include <vector>

#include "object.hpp"

namespace Tracer::Rendering {
    class Scene {
    private:
        std::vector<std::unique_ptr<Objects::Object>> objects;

    public:
        Scene();

        std::vector<std::unique_ptr<Objects::Object>> GetSceneObjects() const;

        void AddObject(Objects::Object object);

        void RemoveObject(std::string tag);
    };
}  // namespace Tracer::Rendering