#include "timing.h"
#include <GLFW/glfw3.h>

double Timing::fps = 0;
double Timing::currentTime = 0;
double Timing::delta = 0;
double Timing::frames = 0;
double Timing::lastTick = 0;

long long second_in_nano = 1000000000;

/**
 * \brief Met ? jour les informations li?es au temps du jeu (Images par secondes, temps entre deux images etc...)
 */
void Timing::update()
{
    delta = currentTime;
    currentTime = glfwGetTime();
    frames++;

    if (currentTime - lastTick >= 1.0)
    {
        lastTick = currentTime;
        fps = frames;
        std::cout << "FPS : " << fps << " DeltaTime : " << getDeltaTime() << std::endl;
        Timing::frames = 0;
    }
}

/**
 * \brief Permet de r?cup?rer le temps ?coul? depuis la derni?re image/rendu du jeu
 * \return le temps ?coul?
 */
double Timing::getDeltaTime()
{
    return glfwGetTime() - delta;
}
