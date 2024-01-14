#include "includes/glad.h"
#include "includes/glfw3.h"

#include <iostream>


void framebuffer_size_callback(GLFWwindow* window, int width, int height);  // definition unten

// --- settings ---
const unsigned int SCR_HEIGHT = 800;
const unsigned int SCR_WIDTH = 600;

// TODO: move glad.c to includes


int main()
{
    // --- glfw: initialize and configure ---
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // macos only

    // --- glfw window creation ---
    GLFWwindow* window = glfwCreateWindow(SCR_HEIGHT, SCR_WIDTH, "meincraft", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // --- glad: load all OpenGL function pointers ---
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

/* ------------------------------------------------------------------------------------------------------- */
/* --------------------------------------------- render loop --------------------------------------------- */

    while (!glfwWindowShouldClose(window))
    {
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

/* --------------------------------------------- render loop --------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------- */


    glfwTerminate();
    return 0;
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions
    glViewport(0, 0, width, height);
}