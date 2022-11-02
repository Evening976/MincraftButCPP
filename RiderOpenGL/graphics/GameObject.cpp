#include "GameObject.h"

GameObject::GameObject()
{
}

GameObject::GameObject(Model model, glm::vec3 pos, glm::vec3 rotation, float scale) : model(model), pos(pos),
    rotation(rotation), scale(scale)
{
}

/**
 * \brief cr?e et retourne la matrice de transformation (position, en gros) d'un objet du jeu
 * \return la matrice de transformation
 */
glm::mat4 GameObject::getTransformationMatrix()
{
    transformationMatrix = glm::identity<glm::mat4>();
    transformationMatrix = glm::translate(transformationMatrix, pos);
    transformationMatrix = glm::rotate(transformationMatrix, rotation.x, glm::vec3(1, 0, 0));
    transformationMatrix = glm::rotate(transformationMatrix, rotation.y, glm::vec3(0, 1, 0));
    transformationMatrix = glm::rotate(transformationMatrix, rotation.z, glm::vec3(0, 0, 1));
    transformationMatrix = glm::scale(transformationMatrix, glm::vec3(scale));
    return transformationMatrix;
}
