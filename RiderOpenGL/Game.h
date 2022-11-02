#pragma once
#include "window.h"
#include "graphics/renderer.h"
#include "utils/timing.h"
#include "utils/modelloader.h"
#include <cstdlib>
#include <iostream>

class Game
{
public:
    Game() : window(), renderer(window.getWindow()), input(window.getWindow())
    {
    }

    ~Game() = default;
    void init();
    void run();
    [[nodiscard]] GLFWwindow* getWindow() const { return window.getWindow(); }

private:
    void update();
    void render();
    Window window;
    Renderer renderer;
    Camera camera;
    GameObject ent;
    Input input;
};
