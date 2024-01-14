cmake_minimum_required(VERSION 3.27)
project(meincraft)

set(CMAKE_CXX_STANDARD 23)

add_executable(meincraft
        main.cpp
        glad.c
        shader.h
        camera.h
)

target_link_libraries(meincraft
        glfw
        GL
)
