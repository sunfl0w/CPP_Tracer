#include "renderer.hpp"

using namespace OpenCG::Math;

namespace OpenCG::Rendering {
    //public
    Renderer::Renderer(int screenWidth, int screenHeight, Camera* camera) {
        this->screenWidth = screenWidth;
        this->screenHeight = screenHeight;
        this->camera = camera;

        projector = Projector(screenWidth, screenHeight, 1, 100);
        viewport = Viewport(screenWidth, screenHeight, 1, 100);
    }

    ScreenBuffer Renderer::RenderToBuffer(std::vector<Tris> triangles) {
        ScreenBuffer buffer = ScreenBuffer(screenWidth, screenHeight);
        for (Tris triangle : triangles) {
            Vertex v1 = Project(triangle.V1());
            Vertex v2 = Project(triangle.V2());
            Vertex v3 = Project(triangle.V3());

            for (int x = 0; x < screenWidth; x++) {
                for (int y = 0; y < screenHeight; y++) {
                    if (IsScreenPointInTris(v1, v2, v3, x, y)) {
                        buffer.SetPixelColor(x, y, RGB_Color(255, 0, 0));
                    } else {
                        if (buffer.GetPixelColor(x, y).Red() == 0) {
                            buffer.SetPixelColor(x, y, RGB_Color(0, 0, 0));
                        }
                    }
                }
            }
        }
        return buffer;
    }

    //private
    Vertex Renderer::Project(Vertex vertex) {
        Matrix projectedVertex = projector.GetMatrix().MultiplyWith(camera->GetMatrix().MultiplyWith(vertex.ToMatrix()));
        Vec3 transformedVertex = viewport.TransformPoint(Vec3(projectedVertex.GetData()[0], projectedVertex.GetData()[1], projectedVertex.GetData()[2]));
        return Vertex(transformedVertex.X(), transformedVertex.Y(), transformedVertex.Z());
    }

    bool Renderer::IsScreenPointInTris(Vertex v1, Vertex v2, Vertex v3, int x, int y) {
        float area0 = GetAreaOfTriangle(v1.X(), v1.Y(), v2.X(), v2.Y(), v3.X(), v3.Y());
        float area1 = GetAreaOfTriangle(x, y, v2.X(), v2.Y(), v3.X(), v3.Y());
        float area2 = GetAreaOfTriangle(v1.X(), v1.Y(), x, y, v3.X(), v3.Y());
        float area3 = GetAreaOfTriangle(v1.X(), v1.Y(), v2.X(), v2.Y(), x, y);

        if (std::abs(area0 - area1 - area2 - area3) < 0.01f && area0 > 0) {
            return true;
        } else {
            return false;
        }
    }

    float Renderer::GetAreaOfTriangle(float x1, float y1, float x2, float y2, float x3, float y3) {
        return std::abs((x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2)) / 2.0);
    }
}  // namespace OpenCG::Rendering