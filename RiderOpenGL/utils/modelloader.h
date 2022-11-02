#pragma once
#include <GL/glew.h>
#include "../graphics/model.h"
#include <vector>
#include <GLFW/glfw3.h>

/**
 * \brief Classe statique qui permet de charger les images, icones, textures, modèles et objets du jeu.
 */
class Loader
{
public:
    static Model loadModel(const void* vertices, uint32_t vSize, const void* texCoords, uint32_t tSize,
                           const void* indices, uint32_t iSize, const char* fileName);
    static Model loadModelData(const void* vertices, uint32_t vSize, const void* texCoords, uint32_t tSize,
                               const void* indices, uint32_t iSize);
    static Texture loadTexture(const char* filename);
    static void loadIcon(const char* filename, GLFWimage* image);
    static void clean();
private:
    static GLuint createVAO();
    static void storeIndicesBuffer(const void* indices, uint32_t iSize);
    static void storeDataInAttribList(GLuint attribNumber, GLuint vertexCount, const void* data, uint32_t size);
    static void unbind();
    static std::vector<GLuint> vaos;
    static std::vector<GLuint> vbos;
    static std::vector<GLuint> textures;
    ~Loader() = default;
};
