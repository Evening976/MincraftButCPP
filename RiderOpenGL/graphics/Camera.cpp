#include "Camera.h"
#include <iostream>


void Camera::init()
{
}

/**
 * \brief Change la rotation de la camera (voir axes de rotation d'un a?ronef)	
 * \param yaw Rotation sur l'angle X 
 * \param pitch Rotation sur l'angle Y
 */
void Camera::moveRotation(float yaw, float pitch)
{
	if(m_pitch + pitch < 90.0f && m_pitch + pitch > -90.0f){
		m_pitch += pitch;
	}
	else if(m_pitch + pitch > 90){
		m_pitch = 90;
	}
	else if(m_pitch + pitch < -90){
		m_pitch = -90;
	}

	if(m_yaw + yaw < 180 && m_yaw + yaw > -180){
		m_yaw += yaw;
	}
	else if(m_yaw + yaw > 180){
		m_yaw = -180 + yaw;
	}
	else if(m_yaw + yaw < -180){
		m_yaw = 180 + yaw;
	}
}

/**
 * \brief D?place la cam?ra dans le monde
 * \param pos D?placement ? effectuer
 */
void Camera::movePos(glm::vec3 pos)
{
	if(pos.z != 0)
	{
		position.x += sin(glm::radians(m_yaw)) * -1 * pos.z;
		position.z += cos(glm::radians(m_yaw)) * pos.z;
	}
	if(pos.x != 0)
	{
		position.x += sin(glm::radians(m_yaw - 90)) * -1 * pos.x;
		position.z += cos(glm::radians(m_yaw - 90)) * pos.x;
	}

	position.y += pos.y;
}

/**
 * \brief met ? jour la matrice de vue de la cam?ra
 */
void Camera::updateViewMatrix()
{
	viewMatrix = glm::identity<glm::mat4>();
	viewMatrix = glm::rotate(viewMatrix, glm::radians(m_pitch), glm::vec3(1.0f, 0.0f, 0.0f));
	viewMatrix = glm::rotate(viewMatrix, glm::radians(m_yaw), glm::vec3(0.0f, 1.0f, 0.0f));
	viewMatrix = glm::translate(viewMatrix, -position);
}

/**
 * \brief met ? jour la cam?ra (d?placement du joueur etc...)
 * \param input Classe qui g?re les entr?es claviers
 * \param deltaTime temps depuis la derni?re image (-> sert ? se d?placer de mani?res constantes quelques soit le nombre de rafraichissement du jeu)
 */
void Camera::update(Input* input, double deltaTime)
{
	glm::vec3 direction(0.0f);
	if(input->getKey(GLFW_KEY_W))
	{
		direction += glm::vec3(0, 0, -10.f);
	}
	if(input->getKey(GLFW_KEY_S))
	{
		direction += glm::vec3(0, 0, 10.f);
	}
	if(input->getKey(GLFW_KEY_D))
	{
		direction += glm::vec3(10.f, 0, 0);
	}
	if(input->getKey(GLFW_KEY_A))
	{
		direction += glm::vec3(-10.f, 0, 0);
	}

	
	moveRotation(input->getYaw() * 0.1f, input->getPitch() * 0.1f);

	if(direction != glm::vec3(0,0,0))
	{
		direction = glm::normalize(direction);
		direction /= 10;
		movePos(direction.operator*=(40*deltaTime));
	}

	updateViewMatrix();
}
