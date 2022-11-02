#pragma once
#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>

/**
 * \brief Classe qui g?re les entr?es clavier de l'utilisateur/joueur
 */
class Input
{
public:
	Input(GLFWwindow* window);
	bool getKey(int key) const;
	glm::vec2 getMousePos();

	const double getYaw()
	{
		return xpos_ - prevxpos_;
	};

	const double getPitch()
	{
		return ypos_ - prevypos_;
	};

	int keys_[65536];
	void updateMouse();
	~Input() = default;
	
private:
	double xpos_, ypos_, prevxpos_, prevypos_;
	GLFWwindow* window;
};
