//
// Created by mp on 18.08.23.
//

#pragma once

#include <SDL2/SDL.h>
#include <memory>

namespace vlk
{

class Instance
{
public:
    Instance(uint32_t windowWidth, uint32_t windowHeight);
    void Init();
    void RunLoop();
    void DeInit();

    unsigned int GetWindowWidth() const
    {
        return mWindowWidth;
    }
    unsigned int GetWindowHeight() const
    {
        return mWindowHeight;
    }

private:
    void createWindow();

//Private members
    SDL_Window* mWindow;
    unsigned int mWindowWidth;
    unsigned int mWindowHeight;

};

} // vlk