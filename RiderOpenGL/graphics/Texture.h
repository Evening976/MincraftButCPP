#pragma once
#include <GL/glew.h>

/**
 * \brief Structure qui permet de garder en m?moire l'addresse ou est stock?e une texture(= image) en VRAM
 */
struct Texture
{
public:
    Texture();

    Texture(int tex) : id(tex)
    {
    }

    Texture(GLuint tex) : id(tex)
    {
    }

    [[nodiscard]] GLuint getID() const
    {
        return id;
    }

    ~Texture();

private:
    GLuint id;
};
