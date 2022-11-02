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
 * \brief Permet de cr�er un mod�le de A � Z
 * \param vertices Sommets du mod�le
 * \param vSize Nombre de sommets du mod�le
 * \param texCoords Coordoonn�es de la texture dans un atlas
 * \param tSize Nombre de coordoonn�es de texture
 * \param indices Indices du mod�le
 * \param iSize Nombre d'indices du mod�le
 * \param fileName fichier ou se trouve la texture du mod�le
 * \return un mod�le pr�t � �tre utilis�
 */
Model Loader::loadModel(const void* vertices, uint32_t vSize, const void* texCoords, uint32_t tSize,
                        const void* indices, uint32_t iSize, const char* fileName)
{
    return {loadModelData(vertices, vSize, texCoords, tSize, indices, iSize), loadTexture(fileName)};
}


/**
 * \brief Permet de mettre en ram les informations destin�es � dessiner un objet
 * \param vertices Sommets de l'objet
 * \param vSize Nombre de sommets pass�s dans vertices
 * \param texCoords Coordoonn�es en pixel des textures (atlas)
 * \param tSize Nombre de coordoonn�es pass�es dans texCoords
 * \param indices indices... dur � expliquer.
 * \param iSize Nombre d'indices pass�s pr�cedemment
 * \return l'addresse ou est stock�e le mod�le ainsi que la quantit�e de sommets sous forme de mod�le
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
 * \brief charge une image qui pourra �tre appliqu� sur un mod�le, puis la met en m�moire sur le GPU avant de retourner son addresse
 * \param filename chemin (relatif) de l'image � utiliser
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
 * \param image pointeur dans lequel stocker l'image/icone charg�e
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
 * \return adresse affect�e
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
 * \param indices Valeurs � stocker 
 * \param iSize Nombre de valeurs � stocker
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
 * \brief Permet de stocker des donn�es dans la vram
 * \param attribNumber emplacement ou seront stock�e les donn�es
 * \param vertexCount nombre de valeurs pour une donn�e (ex : pour coordoonn�es en 3 dimensions, ce sera 3 (x, y, z) pour une coordoonn�e)
 * \param data donn�es � stocker
 * \param size taille des donn�es � stocker
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
 * \brief Nettoie toutes les textures qui ont �t�e charg�es dans la VRAM
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
