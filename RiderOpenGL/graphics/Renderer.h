#pragma once
#include "camera.h"
#include "GameObject.h"
#include "model.h"
#include "../shader/shadermanager.h"
#include "../utils/loader.h"

/**
 * \brief classe qui g?re le rendu ? l'ecran/la fenetre
 */
class Renderer
{
public:
    Renderer(GLFWwindow* window);
    ~Renderer() = default;

    void init();
    void clear();
    void render(GameObject &ent, const Camera &cam, const glm::mat4 &windowProjMat);
    void bind(Model &model);
    void unbind();
    void prepare(GameObject& ent, const Camera& camera);
private:
    ShaderManager shader;
    GLFWwindow* window;
    Camera camera;
};
