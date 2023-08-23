//
// Created by mp on 18.08.23.
//

#include "RenderVK.h"
#include <SDL_vulkan.h>
#include <vulkan/vulkan.hpp>

namespace vlk
{

void RenderVK::Init(SDL_Window *window)
{
    createInstance(window);
    selectPhyDevice();
}

void RenderVK::Draw()
{

}
void RenderVK::DeInit()
{

}

void RenderVK::createInstance(SDL_Window *window)
{
    vk::ApplicationInfo applicationInfo {
        .pApplicationName   = "A triangle tale",
        .applicationVersion = VK_MAKE_VERSION(1, 0, 0),
        .pEngineName        = "No Engine",
        .engineVersion      = VK_MAKE_VERSION(1, 0, 0),
        .apiVersion         = VK_API_VERSION_1_0
    };

    unsigned int extensionCount = 0;
    SDL_Vulkan_GetInstanceExtensions(window, &extensionCount, nullptr);

    vk::InstanceCreateInfo createInfo{};
    createInfo.pApplicationInfo = &applicationInfo;
}

void RenderVK::selectPhyDevice()
{

}

} // vlk