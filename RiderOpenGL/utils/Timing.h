#pragma once
#include <cstdint>
#include <chrono>
#include <iostream>

/**
 * \brief classe qui sert ? garder une trace du temps, tout le temps.
 */
class Timing
{
public:
    static void update();
    static double getFPS() { return fps; }
    static double getDeltaTime();
private:
    static double fps;
    static double currentTime;
    static double lastTick;
    static double delta;
    static double frames;
    ~Timing() = default;
};
