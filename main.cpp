#include "includes/glad.h"
#include "includes/glfw3.h"

// #define STB_IMAGE_IMPLEMENTATION     // already included in texture.h
// #include "includes/stb_image.h"

#include "includes/glm/glm.hpp"
#include "includes/glm/gtc/matrix_transform.hpp"
#include "includes/glm/gtc/type_ptr.hpp"

#include "shader.h"
#include "camera.h"
#include "block.h"
#include "texture.h"

#include <iostream>
#include <cmath>

// TODO: chunk class
// TODO: include texture in block class

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);  // register current mouse position
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 960;
const unsigned int SCR_HEIGHT = 720;
bool wireframe = false;

// camera
Camera camera(glm::vec3(0.0f, 10.0f, 3.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// time
float deltaTime = 0.0f;	// Time between current frame and last frame
float lastFrame = 0.0f; // Time of last frame


int main() {
    /* --- glfw: initialize and configure --- */
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // macos only

    /* --- glfw window creation --- */
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "meincraft", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // glfw: capture and hide mouse cursor
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    /* --- glad: load all OpenGL function pointers --- */
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // --- configure global opengl state ---
    glEnable(GL_DEPTH_TEST);    // enable depth testing so that objects in front will be drawn in front

    // --- build and compile shader program (shader/shader.h) ---
    Shader shader("shaders/vertex.shader", "shaders/fragment.shader");

    // --- set up vertex data (and buffer(s)) and configure vertex attributes ---
    Block block;

    // --- load and create a texture ---
    Texture texture0("textures/texture.png");
    Texture texture1("textures/texture1.png");
    Texture texture2("textures/texture2.png");


/* ------------------------------------------------------------------------------------------------------- */
/* --------------------------------------------- render loop --------------------------------------------- */

    while (!glfwWindowShouldClose(window)) {

        // per-frame time logic
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
        processInput(window);


        /* =============== hier rendern =============== */

        // set background color
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // texture
        (int)glfwGetTime() % 2 == 0 ? texture0.use() : texture2.use();

        shader.use();

        // pass projection matrix to shader (has to be in render loop bc of zoom)
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        shader.setMat4("projection", projection);

        // TODO: leben nehmen (block class -> chunk class -> world class)
        int size = 10;
        for (int x=0; x<size; x++)
        {
            for (int y=0; y<size; y++)
            {
                for (int z=0; z<size; z++)
                {
                    // calculate the model matrix for each object and pass it to shader before drawing
                    glm::mat4 model = glm::mat4(1.0f);
                    model = glm::translate(model, glm::vec3((float)x, (float)y, (float)z)); // move right and down so chunkmesig
                    // model = glm::translate(model, float(-1 * sin(glfwGetTime())) * glm::vec3(0.0f, 1.0f, 0.0f)); // translate
                    // model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.5f)); // rotate
                    shader.setMat4("model", model);

                    // camera/view transformation
                    glm::mat4 view = camera.GetViewMatrix();
                    shader.setMat4("view", view);

                    // render boxes
                    block.draw();
                }
            }
        }

        /* =============== hier rendern =============== */


        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

/* --------------------------------------------- render loop --------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------- */


    // glfw: terminate, clearing all previously allocated GLFW resources.
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    // camera movement
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        camera.ProcessKeyboard(UP, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
        camera.ProcessKeyboard(DOWN, deltaTime);

    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        camera.ProcessKeyboard(SPRINT, deltaTime);

    // TODO: toggle wireframe
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
        if (wireframe) {
            wireframe = false;
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        } else {
            wireframe = true;
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        }
    }



}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions
    glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called (mouse movement)
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn) {
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse) {   // remove mouse jump on first mouse movement
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    // calculate the mouse's offset between the last and current frame
    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called (zoom)
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}