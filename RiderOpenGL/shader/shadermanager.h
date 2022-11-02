#pragma once
#include <map>
#include <GL/GLEW.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/fwd.hpp>


class ShaderManager
{
public:
    ShaderManager();
    ~ShaderManager();

    void createVertexShader(const GLchar* shaderCode);
    void createFragmentShader(const GLchar* shaderCode);
    GLuint createShader(const GLchar* shaderCode, GLenum type);
    GLuint linkProgram(GLuint vertexShaderID, GLuint fragmentShaderID);
    void createUniform(GLchar* uniformName);
    void createUniform(const char* uniformName);
    void link();
    void bind();
    void unbind();


    void setUniform(const GLchar* uniformName, glm::mat4 value);
    void setUniform(GLchar* uniformName, int value);
    void setUniform(GLchar* uniformName, float value);
    void setUniform(GLchar* uniformName, glm::vec3& value);
    void setUniform(GLchar* uniformName, glm::vec4& value);
    void setUniform(GLchar* uniformName, bool value);
    //void setUniform(char* uniformName, glm::mat4 value);
    void setUniform(const char* uniformName, int value);
    void setUniform(const char* uniformName, float value);
    void setUniform(const char* uniformName, glm::vec3& value);
    void setUniform(const char* uniformName, glm::vec4& value);
    void setUniform(const char* uniformName, bool value);
private:
    GLuint programID;
    GLuint vertexShaderID;
    GLuint fragmentShaderID;
    std::map<GLchar*, int> uniforms;
};
