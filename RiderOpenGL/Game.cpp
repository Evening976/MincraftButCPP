#include "game.h"
#include "world/BlockData.h"

/**
 * \brief lancement du jeu
 */
void Game::init()
{
    window.init();
    renderer.init();

    const auto model = Loader::loadModel(BlockData::vertices, sizeof(BlockData::vertices), BlockData::texCoords,
                                         sizeof(BlockData::texCoords), BlockData::indices, sizeof(BlockData::indices),
                                         BlockData::filePath);

    ent = GameObject(model, glm::vec3(0.0f, 0.0f, -2.0f), glm::vec3(0.0f, 0.0f, 0.0f), 1);
}

/**
 * \brief boucle principale du jeu
 */
void Game::run()
{
    while (!glfwWindowShouldClose(window.getWindow()))
    {
        update();
        render();
    }

    Loader::clean();
}

/**
 * \brief Met à jour le jeu dans son entiereté
 */
void Game::update()
{
    glfwPollEvents();

    input.updateMouse();
    camera.update(&input, Timing::getDeltaTime());
    Timing::update();

    if (input.getKey(GLFW_KEY_ESCAPE))
    {
        glfwSetWindowShouldClose(window.getWindow(), true);
    }
}

/**
 * \brief rend l'image à l'écran
 */
void Game::render()
{
    renderer.render(ent, camera, window.getProjectionMatrix());
    glfwSwapBuffers(window.getWindow());
}
