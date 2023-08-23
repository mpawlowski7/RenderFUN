//
// Created by mp on 21.08.23.
//

#include "RenderGL.h"

#include <glad/glad.h>
#include <fmt/format.h>

namespace ogl
{

void RenderGL::Init(SDL_Window* window)
{
    createInstance();
    createContext(window);
}

void RenderGL::Draw(GLuint shaderProgram, GLuint vertexArray, GLuint* vertexBuffer)
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shaderProgram);

    glBindVertexArray(vertexArray);

    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer[0]);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid *)0);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer[1]);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid *)0);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

void RenderGL::DeInit()
{
    if (mContext != nullptr) {
        SDL_GL_DeleteContext(mContext);
    }
}

void RenderGL::createContext(SDL_Window* window)
{
    mContext = SDL_GL_CreateContext(window);
    if (mContext == nullptr) {
        SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "Could not create OpenGL context: %s", SDL_GetError());
    }
}

void RenderGL::createInstance()
{
    if (mContext == nullptr) {
        return;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 0);
    SDL_GL_SetAttribute(SDL_GL_SHARE_WITH_CURRENT_CONTEXT, 1);

    gladLoadGLLoader(SDL_GL_GetProcAddress);
    fmt::print("Vendor:   {}\n", (char *)glGetString(GL_VENDOR));
    fmt::print("Renderer: {}\n", (char *)glGetString(GL_RENDERER));
    fmt::print("Version:  {}\n", (char *)glGetString(GL_VERSION));
}

} // ogl