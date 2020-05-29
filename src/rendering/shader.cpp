#include "shader.hpp"

namespace Tracer::Rendering {
    Shader::Shader() {}

    Shader::Shader(std::string vertexShaderPath, std::string fragmentShaderPath) {
        std::ifstream vertexShaderFileStream;
        std::ifstream fragmentShaderFileStream;
        std::stringstream vertexShaderStringStream;
        std::stringstream fragmentShaderStringStream;

        vertexShaderFileStream.open(vertexShaderPath);
        vertexShaderStringStream << vertexShaderFileStream.rdbuf();
        vertexShaderFileStream.close();

        fragmentShaderFileStream.open(fragmentShaderPath);
        fragmentShaderStringStream << fragmentShaderFileStream.rdbuf();
        fragmentShaderFileStream.close();

        //Compiling vertex shader
        std::string vertexShaderCode = vertexShaderStringStream.str();
        const char* vertexShaderCodePtr = vertexShaderCode.c_str();
        unsigned int vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShaderID, 1, &vertexShaderCodePtr, NULL);
        glCompileShader(vertexShaderID);
        //Check for vertex shader compile errors
        int vsuccess;
        char vinfoLog[512];
        glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &vsuccess);
        if (!vsuccess) {
            glGetShaderInfoLog(vertexShaderID, 512, NULL, vinfoLog);
            std::cout << "Vertex shader compilation failed. Log:\n"
                      << vinfoLog << std::endl;
        }

        //Compiling fragment shader
        std::string fragmentShaderCode = fragmentShaderStringStream.str();
        const char* fragmentShaderCodePtr = fragmentShaderCode.c_str();
        unsigned int fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShaderID, 1, &fragmentShaderCodePtr, NULL);
        glCompileShader(fragmentShaderID);
        //Check for fragment shader compile errors
        int fsuccess;
        char finfoLog[512];
        glGetShaderiv(fragmentShaderID, GL_COMPILE_STATUS, &fsuccess);
        if (!fsuccess) {
            glGetShaderInfoLog(fragmentShaderID, 512, NULL, finfoLog);
            std::cout << "Fragment shader compilation failed. Log:\n"
                      << finfoLog << std::endl;
        }

        //Link shaders
        ID = glCreateProgram();
        glAttachShader(ID, vertexShaderID);
        glAttachShader(ID, fragmentShaderID);
        glLinkProgram(ID);
        //Check for linking errors
        int psuccess;
        char pinfoLog[512];
        glGetProgramiv(ID, GL_LINK_STATUS, &psuccess);
        if (!psuccess) {
            glGetProgramInfoLog(ID, 512, NULL, pinfoLog);
            std::cout << "Shader linking failed. Log:\n"
                      << pinfoLog << std::endl;
        }
        glDeleteShader(vertexShaderID);
        glDeleteShader(fragmentShaderID);
    }

    void Shader::Activate() {
        glUseProgram(ID);
    }

    unsigned int Shader::GetID() {
        return ID;
    }

    void Shader::SetInt(std::string name, int value) {
        unsigned int uniformLocation = glGetUniformLocation(ID, name.c_str());
        glUniform1i(uniformLocation, value);
    }

    void Shader::SetVec4(std::string name, glm::vec4 vector) {
        glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, glm::value_ptr(vector));
    }

    void Shader::SetMat4(std::string name, glm::mat4 matrix) {
        unsigned int uniformLocation = glGetUniformLocation(ID, name.c_str());
        glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(matrix));
    }
}  // namespace Tracer::Rendering