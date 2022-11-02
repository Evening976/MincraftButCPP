#pragma once
#include "texture.h"

/**
 * \brief sert ? stocker les textures et primitifs de chaque objet du jeu
 */
class Model
{
public:
    Model() = default;

    Model(GLuint ID, int vertexCount): vertexCount(vertexCount), id(ID)
    {
    }

    Model(GLuint ID, int vertexCount, Texture tex) : vertexCount(vertexCount), id(ID), texture(tex)
    {
    } // NOLINT(readability-inconsistent-declaration-parameter-name)
    Model(Model model, Texture tex) : vertexCount(model.getVertexCount()), id(model.getVaoID()), texture(tex)
    {
    }

    ~Model() = default;
    [[nodiscard]] GLuint getVaoID() const { return id; }
    [[nodiscard]] int getVertexCount() const { return vertexCount; }
    [[nodiscard]] Texture getTexture() const { return texture; }
    void setTexture(Texture tex) { texture = tex; }
private:
    int vertexCount;
    GLuint id;
    Texture texture;
};
