cmake_minimum_required(VERSION 3.21)
project(RenderFun CXX C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 20)

# Find and install using vcpkg
find_package(SDL2 CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(Vulkan REQUIRED)

add_executable(RenderFUN code/main.cpp
        code/vlk/RenderVK.cpp
        code/vlk/RenderVK.h
        code/vlk/Instance.cpp
        code/vlk/Instance.h
        code/ogl/RenderGL.cpp
        code/ogl/RenderGL.h)

target_link_libraries(RenderFUN
        PRIVATE SDL2::SDL2
        PRIVATE fmt::fmt
        PRIVATE glad::glad
        PRIVATE glm::glm
        PRIVATE Vulkan::Vulkan)