#include "shadermanager.h"

#include <exception>
#include <iostream>
#include <ostream>
#include <sstream>

ShaderManager::ShaderManager()
{
    programID = glCreateProgram();
    if (programID == 0)
    {
        throw std::runtime_error("Could not create program");
    }
}

ShaderManager::~ShaderManager()
{
    unbind();
    if (programID != 0)
    {
        glDeleteProgram(programID);
    }
}

/**
 * \brief cr?e un programme (GPU) qui permet de g?rer comment les objets sont rendus ? l'?cran
 * \param shaderCode code du programme
 */
void ShaderManager::createVertexShader(const GLchar* shaderCode)
{
    vertexShaderID = createShader(shaderCode, GL_VERTEX_SHADER);
    delete [] shaderCode;
}

/**
 * \brief cr?e un programme (GPU) qui permet de modifier l'apparence d'une texture
 * \param shaderCode code du programme
 */
void ShaderManager::createFragmentShader(const GLchar* shaderCode)
{
    fragmentShaderID = createShader(shaderCode, GL_FRAGMENT_SHADER);
    delete [] shaderCode;
}

/**
 * \brief cr?e un programme (GPU) qui permet de g?rer le rendu des objets ou des textures ? l'?cran
 * \param shaderCode code (source) du programme GLSL
 * \param type peut-?tre de type GL_FRAGMENT_SHADER ou GL_VERTEX_SHADER
 * \return retourne l'ID du programme (son addresse en quelques sortes)
 */
GLuint ShaderManager::createShader(const GLchar* shaderCode, GLenum type)
{
    GLuint shaderID = glCreateShader(type);

    glShaderSource(shaderID, 1, &shaderCode, nullptr);
    glCompileShader(shaderID);


    GLint validation = 0;
    GLchar log[512];
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &validation);

    if (!validation)
    {
        glGetShaderInfoLog(programID, sizeof(log), nullptr, log);
        std::cout << "Unable to load shader : " << std::string(log) << std::endl;
        throw std::runtime_error("Unable to load shader : " + std::string(log));
    }


    glAttachShader(programID, shaderID);

    return shaderID;
}

GLuint ShaderManager::linkProgram(GLuint vertexShaderID, GLuint fragmentShaderID)
{
    glAttachShader(programID, vertexShaderID);
    glAttachShader(programID, fragmentShaderID);

    glLinkProgram(programID);

    return programID;
}

void ShaderManager::createUniform(GLchar* uniformName)
{
    GLint uniformLocation = glGetUniformLocation(programID, uniformName);
    if (uniformLocation < 0)
    {
        std::cout << uniformName << " not found." << std::endl;
    }

    uniforms[uniformName] = uniformLocation;
}

void ShaderManager::createUniform(const char* uniformName)
{
    createUniform(const_cast<GLchar*>(uniformName));
}


void ShaderManager::link()
{
    glLinkProgram(programID);

    if (vertexShaderID != 0)
        glDetachShader(programID, vertexShaderID);

    if (fragmentShaderID != 0)
        glDetachShader(programID, fragmentShaderID);

    glValidateProgram(programID);
}

void ShaderManager::bind()
{
    glUseProgram(programID);
}

void ShaderManager::unbind()
{
    glUseProgram(0);
}

void ShaderManager::setUniform(const GLchar* uniformName, glm::mat4 value)
{
    glUseProgram(programID);
    glUniformMatrix4fv(uniforms[(GLchar*)uniformName], 1, false, glm::value_ptr(value));
}

void ShaderManager::setUniform(GLchar* uniformName, int value)
{
    glUseProgram(programID);
    glUniform1i(uniforms[uniformName], value);
}

void ShaderManager::setUniform(GLchar* uniformName, float value)
{
    glUseProgram(programID);
    glUniform1f(uniforms[uniformName], value);
}

void ShaderManager::setUniform(GLchar* uniformName, glm::vec3& value)
{
    glUseProgram(programID);
    glUniform3f(uniforms[uniformName], value.x, value.y, value.z);
}

void ShaderManager::setUniform(GLchar* uniformName, glm::vec4& value)
{
    glUseProgram(programID);
    glUniform4f(uniforms[uniformName], value.x, value.y, value.z, value.w);
}

void ShaderManager::setUniform(GLchar* uniformName, bool value)
{
    glUseProgram(programID);
    glUniform1i(uniforms[uniformName], value ? 1 : 0);
}


void ShaderManager::setUniform(const char* uniformName, int value)
{
    glUseProgram(programID);
    glUniform1i(uniforms[const_cast<GLchar*>(uniformName)], value);
}

void ShaderManager::setUniform(const char* uniformName, float value)
{
    glUseProgram(programID);
    glUniform1f(uniforms[const_cast<GLchar*>(uniformName)], value);
}

void ShaderManager::setUniform(const char* uniformName, glm::vec3& value)
{
    glUseProgram(programID);
    glUniform3f(uniforms[const_cast<GLchar*>(uniformName)], value.x, value.y, value.z);
}

void ShaderManager::setUniform(const char* uniformName, glm::vec4& value)
{
    glUseProgram(programID);
    glUniform4f(uniforms[const_cast<GLchar*>(uniformName)], value.x, value.y, value.z, value.w);
}

void ShaderManager::setUniform(const char* uniformName, bool value)
{
    glUseProgram(programID);
    glUniform1i(uniforms[const_cast<GLchar*>(uniformName)], value ? 1 : 0);
}
