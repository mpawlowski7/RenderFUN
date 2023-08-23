//
// Created by mp on 18.08.23.
//

#include "Instance.h"
#include <fmt/format.h>

namespace vlk
{

Instance::Instance(uint32_t windowWidth, uint32_t windowHeight)
: mWindow(nullptr),
  mWindowWidth(windowWidth),
  mWindowHeight(windowHeight)
{
}

void Instance::Init()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "Unable to initialize SDL: %s", SDL_GetError());
    }

    fmt::printf("SDL_GetCurrentVideoDriver(): %s\n", SDL_GetCurrentVideoDriver());
}

void Instance::RunLoop()
{
    SDL_Event event;
    while (true) {
        SDL_GL_SwapWindow(mWindow);

        SDL_PollEvent(&event);
        if (event.type == SDL_QUIT)
            break;
    }
}

void Instance::createWindow()
{
    mWindow = SDL_CreateWindow("The triangle tale", 0, 0, mWindowWidth, mWindowHeight,
                                          SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
                                          SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    if (mWindow == nullptr) {
        SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "Could not create window: %s", SDL_GetError());
    }

}
void Instance::DeInit()
{
    SDL_DestroyWindow(mWindow);
    SDL_Quit();
}
} // vlk