//
// Created by mp on 21.08.23.
//

#pragma once

#include <glad/glad.h>
#include <SDL2/SDL.h>

namespace ogl
{

class RenderGL
{
public:
    void Init(SDL_Window* window);
    void Draw(GLuint shaderProgram, GLuint vertexArray, GLuint* vertexBuffer);
    void DeInit();

private:
    void createContext(SDL_Window* window);
    void createInstance();

//Private members
    SDL_GLContext mContext;

};

} // ogl