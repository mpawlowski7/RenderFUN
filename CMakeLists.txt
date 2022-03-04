cmake_minimum_required(VERSION 3.21)
project(DataVisGL CXX C)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR})
list(APPEND CMAKE_PREFIX_PATH ${CMAKE_BINARY_DIR})

set(CMAKE_CXX_STANDARD 14)
include(cmake/conan.cmake)

conan_cmake_configure(REQUIRES
        fmt/8.1.1
        glad/0.1.34
        glm/0.9.9.8
        GENERATORS cmake_find_package)

conan_cmake_install(PATH_OR_REFERENCE .
        BUILD missing)

find_package(SDL2 REQUIRED)
find_package(fmt)
find_package(glad)
find_package(glm)

add_executable(DataVisGL main.cpp)

target_link_libraries(DataVisGL SDL2::SDL2 fmt::fmt glad::glad glm::glm)