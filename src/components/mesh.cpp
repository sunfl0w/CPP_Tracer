#include "mesh.hpp"

namespace OpenCG::Components {
    Mesh::Mesh() {
        data = std::vector<Tris>();
    }

    void Mesh::LoadFromObjectFile(std::string filePath) {
        std::fstream objectFile;
        objectFile.open(filePath);

        std::vector<std::string> lines;
        std::string string;
        while(std::getline(objectFile, string)) {
            lines.push_back(string);
        }        
        objectFile.close();
        
        std::vector<Vertex> vertecies;
        std::vector<Tris> triangles;

        for(std::string line : lines) {
            size_t pos;
            pos = line.find("v ");
            if(pos != std::string::npos) {
                Vertex vertex;
                size_t coordinateStartPos = 0;
                for(int i = 0; i < 3; i++) {
                    coordinateStartPos = line.find(" ", coordinateStartPos);
                    if(line[coordinateStartPos + 1] == '-') {
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
            if(pos != std::string::npos) {
                Tris triangle;
                size_t vertexStartPos = 0;
                for(int i = 0; i < 3; i++) {
                    vertexStartPos = line.find(" ", vertexStartPos);                   
                    triangle.Set(i,  vertecies[std::stoi(line.substr(vertexStartPos + 1, 1)) - 1]);
                    vertexStartPos += 2;
                }
                triangles.push_back(triangle);
            }
        }
        data = triangles;
    }

    std::vector<Tris> Mesh::GetData() {
        return data;
    }
}