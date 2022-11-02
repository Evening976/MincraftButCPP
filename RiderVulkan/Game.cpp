#include "Game.h"
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

void Game::init()
{

    const auto pfnCreateInstance = reinterpret_cast<PFN_vkCreateInstance>(glfwGetInstanceProcAddress(NULL, "vkCreateInstance"));
    if(pfnCreateInstance == nullptr)
    {
        std::cout << "Could not create an instance. Vulkan may not be available." << std::endl;
    }

    const auto pfnPhysicalDevice = reinterpret_cast<PFN_vkCreateDevice>(glfwGetInstanceProcAddress(m_instance, "vkCreateDevice"));

    uint32_t count;
    const char** extensions = glfwGetRequiredInstanceExtensions(&count);

    if(extensions == nullptr)
    {
        std::cout << "No extensions found." << std::endl;
    }

    VkInstanceCreateInfo ici;

    memset(&ici, 0, sizeof(ici));
    ici.enabledExtensionCount = count;
    ici.ppEnabledExtensionNames = extensions;
    ici.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;

    if(!glfwGetPhysicalDevicePresentationSupport(m_instance, physical_device, queue_family_index))
    {
        std::cout << "Presentation is not supported." << std::endl;
    }
}

void Game::run()
{
}
