#ifndef WINDOW_H
#define WINDOW_H

#include "settings.h"


// not a true window class, callbacks are still in game.h

class Window
{
public:
    Window()
    {
        init_opengl();
    }



    void init_opengl() // window initialization
    {
        /* --- glfw: initialize and configure --- */
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        /* --- glfw window creation --- */
        GLFWwindow* window = glfwCreateWindow(g_width, g_height, "hier kommt eh fps", NULL, NULL);
        if (window == NULL)
        {
            std::cout << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
        }
        glfwMakeContextCurrent(window);


        // glfw: capture and hide mouse cursor
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

        /* --- glad: load all OpenGL function pointers --- */
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cout << "Failed to initialize GLAD" << std::endl;
        }

        // --- configure global opengl state ---
        glEnable(GL_DEPTH_TEST);    // enable depth testing so that objects in front will be drawn in front
        // glEnable(GL_DEBUG_OUTPUT); // enable debug output

        // // kaputt  // TODO: fix
        // glEnable(GL_CULL_FACE);     // enable culling of faces
        // glFrontFace(GL_CW);         // front faces are clockwise
        // glCullFace(GL_BACK);        // cull back faces


        p_win = window;
    }
};



#endif
