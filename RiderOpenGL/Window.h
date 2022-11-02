#pragma once
#include <GL/GLEW.h>
#include <GLFW/glfw3.h>
#include <glm/fwd.hpp>
#include <glm/glm.hpp>
#include <iostream>
#include <ostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "utils/modelloader.h"
#include "utils/defaultSettings.h"

/**
 * \brief Fen�tre du jeu
 */
class Window
{
public:
    Window();
    ~Window();

    void init();
    /**
     * \brief pointeur vers la fen�tre ou a lieu le rendu du jeu
     * \return retourne le pointeur
     */
    GLFWwindow* getWindow() const { return window; }
    glm::mat4 getProjectionMatrix();
private:
    GLFWwindow* window{};
};
