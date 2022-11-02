#include "input.h"
#include <iostream>


Input::Input(GLFWwindow* windowHandle): window(windowHandle)
{
}

/**
 * \brief Permet de v�rifier si l'utilisateur/joueur est en train d'appuyer ou de maintenir une touche du clavier
 * \param key Touche dont il faut v�rifier l'�tat
 * \return Vrai si la touche est press�e/maintenu, sinon faux
 */
bool Input::getKey(int key) const
{
	return glfwGetKey(window, key) == (GLFW_REPEAT || GLFW_PRESS);
}

/**
 * \brief Met � jour la position de la souris et renvoie son d�placement par rapport � la derniere mise a jour
 * \return Vecteur du d�placement souris
 */
glm::vec2 Input::getMousePos()
{
	updateMouse();
	return { xpos_ - prevxpos_, ypos_ - prevypos_ };
}

/**
 * \brief met � jour la position de la souris
 */
void Input::updateMouse()
{
	prevxpos_ = xpos_;
	prevypos_ = ypos_;
	glfwGetCursorPos(window, &xpos_, &ypos_);
}