#include <fmt/printf.h>
#include <glad/glad.h>
#include <SDL2/SDL.h>

static GLuint vbo[2];
static GLuint vao;
static GLuint shaderProgram;
static const GLuint g_windowWidth = 1280, g_windowHeight = 720;

static void prepareBuffers() {
    const GLfloat vertices[2][9] = {{0.4f, -0.8f, 0.0f, -0.8f, -0.8f, 0.0f, -0.8f, 0.8f, 0.0f},
                                    {0.8f, 0.8f, 0.0f, -0.4f, 0.8f, 0.0f, 0.8f, -0.8f, 0.0f}};

    glGenVertexArrays(1, &vao);
    glGenBuffers(2, vbo);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]), vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[1]), vertices[1], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)nullptr);
    glEnableVertexAttribArray(0);
}

static void prepareShaders() {
    const char *vertShaderSource = "#version 330 core\n"
                                   "layout (location = 0) in vec3 aPos;\n"
                                   "out vec3 outColor;\n"
                                   "void main()\n"
                                   "{\n"
                                   "    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                   "    outColor = aPos;\n"
                                   "}";

    const char *fragShaderSource = "#version 330 core\n"
                                   "in vec3 outColor;\n"
                                   "out vec4 fragColor;\n"
                                   "void main()\n"
                                   "{\n"
                                   "    fragColor = vec4((outColor / 2) + 0.5f, 1.0);\n"
                                   "}";

    int success;
    std::string infoLog(512, ' ');

    uint32_t vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertShaderSource, nullptr);
    glCompileShader(vertexShader);

    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, nullptr, &infoLog[0]);
        fmt::printf("ERROR::SHADER::VERTEX::COMPILATION_FAILED {}\n", infoLog);
    }

    uint32_t fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragShaderSource, nullptr);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, nullptr, &infoLog[0]);
        fmt::printf("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n %s", infoLog);
    }

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, nullptr, &infoLog[0]);
        fmt::printf("ERROR::PROGRAM::LINK::FAILED {}\n", infoLog);
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

int main() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "Unable to initialize SDL: %s", SDL_GetError());
        return -1;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 0);
    SDL_GL_SetAttribute(SDL_GL_SHARE_WITH_CURRENT_CONTEXT, 1);

    fmt::printf("SDL_GetCurrentVideoDriver(): %s\n", SDL_GetCurrentVideoDriver());

    SDL_Window *window = SDL_CreateWindow("The triangle tale", 0, 0, g_windowWidth, g_windowHeight,
                                          SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "Could not create window: %s", SDL_GetError());
        return -1;
    }

    SDL_GLContext context = SDL_GL_CreateContext(window);
    if (context == nullptr) {
        SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "Could not create OpenGL context: %s", SDL_GetError());
        return -1;
    }

    gladLoadGLLoader(SDL_GL_GetProcAddress);
    fmt::printf("Vendor:   %s\n", glGetString(GL_VENDOR));
    fmt::printf("Renderer: %s\n", glGetString(GL_RENDERER));
    fmt::printf("Version:  %s\n", glGetString(GL_VERSION));

    prepareBuffers();
    prepareShaders();

    glViewport(0, 0, g_windowWidth, g_windowHeight);

    SDL_Event event;
    while (true) {
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);

        glBindVertexArray(vao);

        glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid *)0);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid *)0);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        SDL_GL_SwapWindow(window);

        SDL_PollEvent(&event);
        if (event.type == SDL_QUIT)
            break;
    }

    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(2, vbo);
    glDeleteProgram(shaderProgram);

    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
