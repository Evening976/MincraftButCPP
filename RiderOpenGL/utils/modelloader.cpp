#include "modelloader.h"

#include <iostream>
#include <stdexcept>
#include <string>
#include <GLFW/glfw3.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


std::vector<GLuint> Loader::vaos = std::vector<GLuint>();
std::vector<GLuint> Loader::vbos = std::vector<GLuint>();
std::vector<GLuint> Loader::textures = std::vector<GLuint>();


/**
 * \brief Permet de créer un modèle de A à Z
 * \param vertices Sommets du modèle
 * \param vSize Nombre de sommets du modèle
 * \param texCoords Coordoonnées de la texture dans un atlas
 * \param tSize Nombre de coordoonnées de texture
 * \param indices Indices du modèle
 * \param iSize Nombre d'indices du modèle
 * \param fileName fichier ou se trouve la texture du modèle
 * \return un modèle prêt à être utilisé
 */
Model Loader::loadModel(const void* vertices, uint32_t vSize, const void* texCoords, uint32_t tSize,
                        const void* indices, uint32_t iSize, const char* fileName)
{
    return {loadModelData(vertices, vSize, texCoords, tSize, indices, iSize), loadTexture(fileName)};
}


/**
 * \brief Permet de mettre en ram les informations destinées à dessiner un objet
 * \param vertices Sommets de l'objet
 * \param vSize Nombre de sommets passés dans vertices
 * \param texCoords Coordoonnées en pixel des textures (atlas)
 * \param tSize Nombre de coordoonnées passées dans texCoords
 * \param indices indices... dur à expliquer.
 * \param iSize Nombre d'indices passés précedemment
 * \return l'addresse ou est stockée le modèle ainsi que la quantitée de sommets sous forme de modèle
 */
Model Loader::loadModelData(const void* vertices, uint32_t vSize, const void* texCoords, uint32_t tSize,
                            const void* indices, uint32_t iSize)
{
    GLuint vaoID = createVAO();
    storeIndicesBuffer(indices, iSize);
    storeDataInAttribList(0, 3, vertices, vSize);
    storeDataInAttribList(1, 2, texCoords, tSize);
    unbind();
    return {vaoID, static_cast<int>(iSize / sizeof(GLuint))};
}


/**
 * \brief charge une image qui pourra être appliqué sur un modèle, puis la met en mémoire sur le GPU avant de retourner son addresse
 * \param filename chemin (relatif) de l'image à utiliser
 * \return addresse de l'image en VRAM
 */
Texture Loader::loadTexture(const char* filename)
{
    int width, height, channels;

    unsigned char* buffer = stbi_load(filename, &width, &height, &channels, 4);

    if (buffer == nullptr)
    {
        std::cout << "Failed to load image " << filename << " : " << stbi_failure_reason() << std::endl;
    }

    GLuint id{};
    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, buffer);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(buffer);

    textures.push_back(id);

    return {id};
}

/**
 * \brief Permet de charger une icone
 * \param filename Chemin vers l'image/icone
 * \param image pointeur dans lequel stocker l'image/icone chargée
 */
void Loader::loadIcon(const char* filename, GLFWimage* image)
{
    int width, height, channels;

    unsigned char* buffer = stbi_load(filename, &width, &height, &channels, 4);
    if (buffer == nullptr)
    {
        std::cout << "Failed to load image " << filename << " : " << stbi_failure_reason() << std::endl;
    }

    image->width = width;
    image->height = height;
    image->pixels = buffer;

    stbi_image_free(buffer);
}

/**
 * \brief Attribue un emplacement dans la vram et retourne son adresse
 * \return adresse affectée
 */
GLuint Loader::createVAO()
{
    GLuint vaoID;
    glGenVertexArrays(1, &vaoID);
    glBindVertexArray(vaoID);
    Loader::vaos.push_back(vaoID);
    return vaoID;
}

/**
 * \brief Stocke des "sommets" dans la vram
 * \param indices Valeurs à stocker 
 * \param iSize Nombre de valeurs à stocker
 */
void Loader::storeIndicesBuffer(const void* indices, uint32_t iSize)
{
    GLuint vbo;
    glGenBuffers(1, &vbo);
    Loader::vbos.push_back(vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, iSize, indices, GL_STATIC_DRAW);
}

/**
 * \brief Permet de stocker des données dans la vram
 * \param attribNumber emplacement ou seront stockée les données
 * \param vertexCount nombre de valeurs pour une donnée (ex : pour coordoonnées en 3 dimensions, ce sera 3 (x, y, z) pour une coordoonnée)
 * \param data données à stocker
 * \param size taille des données à stocker
 */
void Loader::storeDataInAttribList(GLuint attribNumber, GLuint vertexCount, const void* data, uint32_t size)
{
    GLuint vbo;
    glGenBuffers(1, &vbo);
    Loader::vbos.push_back(vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    glVertexAttribPointer(attribNumber, vertexCount, GL_FLOAT, GL_FALSE, sizeof(float) * vertexCount, 0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Loader::unbind()
{
    glBindVertexArray(0);
}

/**
 * \brief Nettoie toutes les textures qui ont étée chargées dans la VRAM
 */
void Loader::clean()
{
    for (auto vao : vaos)
    {
        glDeleteVertexArrays(1, &vao);
    }
    for (auto vbo : vbos)
    {
        glDeleteVertexArrays(1, &vbo);
    }

    for (auto tex : textures)
    {
        glDeleteVertexArrays(1, &tex);
    }
}
