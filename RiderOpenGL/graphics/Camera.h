#pragma once
#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <glm/ext/matrix_transform.hpp>
#include "../input/input.h"

/**
 * \brief classe qui gère la caméra, le point de vue du joueur
 */
class Camera
{
public:
    Camera() : position(0.0f, 0.0f, -1.0f), m_yaw(1.0f), m_pitch(1.0f), mouseSensitivity(0.1f)
    {
    }

    void init();
    void moveRotation(float yaw, float pitch);
    void movePos(glm::vec3 pos);
    void update(Input* input, double deltaTime);
    ~Camera() = default;

    /**
     * \brief retourne la matrice de vue de la caméra (du joueur)
     * \return 
     */
    glm::mat4 getViewMatrix() const { return viewMatrix; };

    /**
     * \brief 
     * \return retourne la position du joueur en un vecteur 3d
     */
    glm::vec3 getPosition() const { return position; };

private:
    void updateViewMatrix();

    glm::mat4 viewMatrix{};

    glm::vec3 position{};

    float m_yaw, m_pitch;
    float mouseSensitivity;
};
