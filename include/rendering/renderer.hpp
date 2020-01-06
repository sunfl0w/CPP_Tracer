#pragma once

#include <vector>

#include "tris.hpp"
#include "screenBuffer.hpp"
#include "projector.hpp"
#include "camera.hpp"
#include "viewport.hpp"
#include "matrix.hpp"

namespace OpenCG::Rendering {
    class Renderer {
    private:
        int screenWidth;
        int screenHeight;
        Camera* camera;
        Projector projector;
        Viewport viewport;

    public:
        Renderer(int screenWidth, int screenHeight, Camera* camera);
        ScreenBuffer RenderToBuffer(std::vector<Tris> triangles);

    private:
        Vertex Project(Vertex vertex);
        bool IsScreenPointInTris(Vertex v1, Vertex v2, Vertex v3, int x, int y);
        float GetAreaOfTriangle(float x1, float y1, float x2, float y2, float x3, float y3);
    };  
}  // namespace OpenCG::Renderer