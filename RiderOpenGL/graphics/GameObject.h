#pragma once
#include <glm/fwd.hpp>
#include <glm/vec3.hpp>
#include <glm/ext/matrix_transform.hpp>
#include "model.h"

/**
 * \brief Objet du jeu (Ex : un cube dans Minecraft)
 */
class GameObject
{
public:
    GameObject();
    GameObject(Model model, glm::vec3 pos, glm::vec3 rotation, float scale);
    ~GameObject() = default;

    /**
     * \brief Incr?mente la position de l'objet
     * \param v d?placement ? effectuer
     */
    void incPos(glm::vec3 v) { pos += v; }

    /**
     * \brief donne la position de l'objet sous forme de vecteur 3d
     * \return vecteur position
     */
    glm::vec3 getPos() const { return pos; }

    /**
     * \brief Donne une nouvelle position ? l'objet
     * \param newPos Coordoonn?es de la nouvelle positon
     */
    void setPos(glm::vec3 newPos) { pos = newPos; }

    /**
     * \brief Incr?mente la rotation de l'objet
     * \param v degr? d'incr?mentation sous forme de vecteur
     */
    void incRot(glm::vec3 v) { rotation += v; }
    /**
     * \brief Donne la rotation de l'objet dans les diff?rents axes sous forme de vecteur 3d
     * \return vecteur rotation
     */
    glm::vec3 getRot() const { return rotation; }

    /**
     * \brief Donne une nouvelle rotation ? l'objet
     * \param v Donn?es de rotation
     */
    void setRot(glm::vec3 v) { rotation = v; }
    /**
     * \brief Donne le mod?le utilis? par l'objet
     * \return copie du mod?le
     */
    Model* getModel() { return &model; }
    Model& getModelbyRef() { return model; }
    void setModel(Model model) { GameObject::model = model; }
    float getScale() const { return scale; }
    void setScale(float v) { scale = v; }

    glm::mat4 getTransformationMatrix();
private:
    Model model;
    glm::vec3 pos;
    glm::vec3 rotation;
    glm::mat4 transformationMatrix;
    float scale;
};
