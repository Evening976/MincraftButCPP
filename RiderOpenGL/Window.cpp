#include "window.h"

/**
 * \brief Créé la fenêtre du jeu
 */
Window::Window()
{
    if (!glfwInit())
    {
        throw std::runtime_error("Failed to initialize GLFW");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_SAMPLES, 4);

    window = glfwCreateWindow(WIDTH, HEIGHT, TITLE, NULL, NULL);
    if (window == nullptr)
    {
        throw std::runtime_error("Failed to create GLFW window");
    }

    const GLFWvidmode* videoMode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    glfwSetWindowPos(window, (videoMode->width - WIDTH) / 2, (videoMode->height - HEIGHT) / 2);

    glfwMakeContextCurrent(window);
    glfwSwapInterval(vSync ? 1 : 0);

    glfwShowWindow(window);

    if (glewInit() != GLEW_OK)
    {
        throw std::runtime_error("Could not load GLEW");
    }

    GLFWimage icon;
    Loader::loadIcon("res//icon//minecraft.png", &icon);
    glfwSetWindowIcon(window, 1, &icon);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

Window::~Window()
{
    glfwDestroyWindow(window);
    glfwTerminate();
}

/**
 * \brief Initialise la fenetre et ses paramètres.
 */
void Window::init()
{
    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_STENCIL_TEST);
    glEnable(GL_MULTISAMPLE);
}

/**
 * \brief construit et retourne la matrice de projection de la fenêtre en utilisant les paramètres du jeu (Champ de vue, distance de vue, format (16:9...))
 * \return la matrice de projection
 */
glm::mat4 Window::getProjectionMatrix()
{
    glm::mat4 projectionMatrix;
    constexpr float aspectRatio = float(16) / float(9);
    projectionMatrix = glm::perspective(glm::radians(FOV), aspectRatio, zNEAR, zFAR);
    return projectionMatrix;
}
