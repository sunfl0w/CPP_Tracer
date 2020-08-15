#include "mesh.hpp"

namespace Tracer::Components {
    Mesh::Mesh() {
        data = std::vector<Math::Tris>();
    }

    void Mesh::LoadFromObjectFile(std::string filePath) {
        if (std::filesystem::path(filePath).extension() != ".obj") {
            std::cout << "The file containing the mesh is not an obj file.\n";
            exit(1);
        }
        std::fstream objectFile;
        objectFile.open(filePath);

        if (!objectFile) {
            std::cout << "Unable to open obj file.\n";
            exit(1);
        }

        std::vector<std::string> lines;
        std::string string;
        while (std::getline(objectFile, string)) {
            lines.push_back(string);
        }
        objectFile.close();

        std::vector<glm::vec3> vertecies;
        std::vector<Math::Tris> triangles;

        for (std::string line : lines) {
            size_t pos;
            pos = line.find("v ");
            if (pos != std::string::npos) {
                glm::vec3 vertex;
                size_t coordinateStartPos = 0;
                for (int i = 0; i < 3; i++) {
                    coordinateStartPos = line.find(" ", coordinateStartPos);
                    if (line[coordinateStartPos + 1] == '-') {
                        if (i == 0) {
                            vertex.x = std::stof(line.substr(coordinateStartPos + 1, 9));
                        } else if (i == 1) {
                            vertex.y = std::stof(line.substr(coordinateStartPos + 1, 9));
                        } else if (i == 2) {
                            vertex.z = std::stof(line.substr(coordinateStartPos + 1, 9));
                        }
                        coordinateStartPos += 10;
                    } else {
                        if (i == 0) {
                            vertex.x = std::stof(line.substr(coordinateStartPos + 1, 8));
                        } else if (i == 1) {
                            vertex.y = std::stof(line.substr(coordinateStartPos + 1, 8));
                        } else if (i == 2) {
                            vertex.z = std::stof(line.substr(coordinateStartPos + 1, 8));
                        }
                        coordinateStartPos += 8;
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
                    if (i == 0) {
                        triangle.vert0 = vertecies[std::stoi(line.substr(vertexStartPos + 1, vertexEndPos - vertexStartPos + 1)) - 1];
                    } else if (i == 1) {
                        triangle.vert1 = vertecies[std::stoi(line.substr(vertexStartPos + 1, vertexEndPos - vertexStartPos + 1)) - 1];
                    } else if (i == 2) {
                        triangle.vert2 = vertecies[std::stoi(line.substr(vertexStartPos + 1, vertexEndPos - vertexStartPos + 1)) - 1];
                    }
                    vertexStartPos += 2;
                }
                triangles.push_back(triangle);
            }
        }
        data = triangles;
    }

    std::vector<Math::Tris>& Mesh::GetData() {
        return data;
    }
}  // namespace Tracer::Components