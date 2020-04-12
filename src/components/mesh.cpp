#include "mesh.hpp"

namespace Tracer::Components {
    Mesh::Mesh() : Component("MeshComponent") {
        data = std::vector<Math::Tris>();
        boundingBox = BoundingBox();
    }

    void Mesh::LoadFromObjectFile(std::string filePath) {
        std::fstream objectFile;
        objectFile.open(filePath);

        std::vector<std::string> lines;
        std::string string;
        while (std::getline(objectFile, string)) {
            lines.push_back(string);
        }
        objectFile.close();

        std::vector<Math::Vec3> vertecies;
        std::vector<Math::Tris> triangles;

        for (std::string line : lines) {
            size_t pos;
            pos = line.find("v ");
            if (pos != std::string::npos) {
                Math::Vec3 vertex;
                size_t coordinateStartPos = 0;
                for (int i = 0; i < 3; i++) {
                    coordinateStartPos = line.find(" ", coordinateStartPos);
                    if (line[coordinateStartPos + 1] == '-') {
                        vertex.Set(i, std::stof(line.substr(coordinateStartPos + 1, 9)));
                        coordinateStartPos += 10;
                    } else {
                        vertex.Set(i, std::stof(line.substr(coordinateStartPos + 1, 8)));
                        coordinateStartPos += 9;
                    }
                }
                vertecies.push_back(vertex);
            }

            pos = line.find("f ");
            if (pos != std::string::npos) {
                Math::Tris triangle;
                size_t vertexStartPos = 0;
                for (int i = 0; i < 3; i++) {
                    vertexStartPos = line.find(" ", vertexStartPos);
                    size_t vertexEndPos = line.find(" ", vertexStartPos + 1);
                    triangle.Set(i, vertecies[std::stoi(line.substr(vertexStartPos + 1, vertexEndPos - vertexStartPos + 1)) - 1]);
                    vertexStartPos += 2;
                }
                triangles.push_back(triangle);
            }
        }
        data = triangles;
        boundingBox = BoundingBox(triangles);
    }

    std::vector<Math::Tris>& Mesh::GetData() {
        return data;
    }

    bool Mesh::RayIntersects(const Math::Ray& ray) const {
        return boundingBox.RayIntersects(ray);
    }
}  // namespace OpenCG::Components