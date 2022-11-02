#include "renderer.h"


Renderer::Renderer(GLFWwindow* windowhandle) : shader(), window(windowhandle)
{
}

/**
 * \brief Initialise les Shaders (voir ShaderManager)
 */
void Renderer::init()
{
    shader.createFragmentShader(read_file("res//shaders//basic.fs"));
    shader.createVertexShader(read_file("res//shaders//basic.vs"));

    shader.link();
    shader.createUniform("textureSampler");
    shader.createUniform("transformationMatrix");
    shader.createUniform("projectionMatrix");
    shader.createUniform("viewMatrix");
}

void Renderer::clear()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

/**
 * \brief Rend un ?l?ment du jeu (GameObject)
 * \param ent Entit?e a rendre
 * \param camera Camera du joueur
 * \param windowProjMat Matrice de projection de la fen?tre
 */
void Renderer::render(GameObject &ent, const Camera &camera, const glm::mat4 &windowProjMat)
{
    clear();
    shader.bind();
    shader.setUniform("projectionMatrix", windowProjMat);
    bind(ent.getModelbyRef());
    prepare(ent, camera);
    glDrawElements(GL_TRIANGLES, ent.getModel()->getVertexCount(), GL_UNSIGNED_INT, 0);

    unbind();
    shader.unbind();
}

/**
 * \brief Attache la texture ? rendre ? OpenGL
 * \param model texture ? rendre
 */
void Renderer::bind(Model &model)
{
    glBindVertexArray(model.getVaoID());
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, model.getTexture().getID());
}

/**
 * \brief "D?sattache" la texture ? rendre
 */
void Renderer::unbind()
{
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glBindVertexArray(0);
}

/**
 * \brief Pr?pare le rendu en mettant ? jour les valeurs qui vont ?tre utilis?es par le Shader
 * \param ent Objet du jeu ? rendre
 * \param camera Camera du jeu
 */
void Renderer::prepare(GameObject &ent, const Camera &camera)
{
    shader.setUniform("textureSampler", 0);
    shader.setUniform("transformationMatrix", ent.getTransformationMatrix());
    shader.setUniform("viewMatrix", camera.getViewMatrix());
}
