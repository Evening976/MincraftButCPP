#pragma once

#include <iostream>
#include <vulkan/vulkan.h>

class Game
{
public:
    void init();
    void run();

private:
    void update();
    void render();
    VkInstance m_instance;
    VkPhysicalDevice physical_device;
    uint32_t queue_family_index;
};
