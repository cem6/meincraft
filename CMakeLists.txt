cmake_minimum_required(VERSION 3.27)
project(meincraft03)

set(CMAKE_CXX_STANDARD 23)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++23 -Wall -Wextra -Wpedantic -Werror")

add_executable(meincraft03
        src/main.cpp
        src/glad.c
        src/settings.h
        src/game.h
        src/window.h
        src/shader.h
        src/camera.h
        src/texture.h

        src/Graphics/VAO.h
        src/Graphics/VBO.h
        src/Graphics/EBO.h

        src/World/block.h
        src/World/chunk.h
        src/World/NEWchunk.h
        includes/FastNoiseLite.h
        src/World/world.h
)

target_link_libraries(meincraft03
        glfw
        GL
)
