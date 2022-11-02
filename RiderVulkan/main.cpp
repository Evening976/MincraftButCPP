#define GLFW_INCLUDE_VULKAN
#include <GLFW/GLFW3.h>

#include "Game.h"

int main(int argc, char* argv[])
{
    Game game;
    game.init();
    game.run();

    
    return 0;
}
