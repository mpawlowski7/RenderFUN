//
// Created by mp on 18.08.23.
//

#pragma once

#include <SDL2/SDL.h>
#include <vulkan/vulkan.hpp>

namespace vlk
{
	class RenderVK
	{
    public:
        void Init(SDL_Window* window);
        void Draw();
        void DeInit();

    private:
        void createInstance(SDL_Window *window);
        void selectPhyDevice();

// Private members
        VkInstance mInstance;
	};

} // vlk