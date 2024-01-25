#ifndef GAME_H
#define GAME_H

#include "settings.h"
#include "shader.h"
#include "camera.h"
#include "texture.h"

#include "Graphics/VBO.h"
#include "Graphics/VAO.h"
#include "Graphics/EBO.h"

#include "World/chunk.h"
#include "World/world.h"

#include <iostream>
#include <vector>






inline Camera camera(glm::vec3(-10.0f, 20.0f, -10.0f));

class Game
{
private:
    Shader *shader;
    Texture *textureWhite;
    Texture *textureWolf;
    Texture *atlas;


public:
    Game()
    {
        // can not be in window.h because callback functions are in game.h // TODO: maybe move callback to window.h
        glfwSetFramebufferSizeCallback(p_win, framebuffer_size_callback);
        glfwSetCursorPosCallback(p_win, mouse_callback);
        glfwSetScrollCallback(p_win, scroll_callback);

        textureWhite = new Texture("../textures/texture_B.png");
        textureWolf = new Texture("../textures/wolf.jpg");
        atlas = new Texture("../textures/0atlas.png");

        shader = new Shader("../shaders/vertex.shader", "../shaders/fragment.shader"); // sollte eigentlich global sein
        shader->use(); // == (*shader).use(); //
        shader->setInt("texture1", 0); // texture unit 0


        std::cout << "Game started" << std::endl;
    }

    ~Game()
    {
        glfwTerminate();
        std::cout << "Game stopped" << std::endl;
    }



    void renderloop()
    {




        World world;






        while (!glfwWindowShouldClose(p_win))
        {
            // per-frame time logic
            float currentFrame = static_cast<float>(glfwGetTime());
            deltaTime = currentFrame - lastFrame;
            lastFrame = currentFrame;

            // fps
            int fps = 1/deltaTime;  // glfw caps at 60 fps
            glfwSetWindowTitle(p_win, std::to_string(fps).c_str());

            // input
            proccessInput(p_win);
            // wireframe mode
            if (wireframe) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            else glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

            // render
            // clear the screen
            glClearColor(0.7f, 0.8f, 1.0f, 1.0f); // state-setting function //0.5f, 0.8f, 1.0f
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            // transformation matrices
            glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first (?)
            model = glm::translate(model, glm::vec3(0.0, 0.0f, 0.0f)); // move backwards
            glm::mat4 view = camera.GetViewMatrix();
            glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)g_width / (float)g_height, 0.1f, /*render distance:*/400.0f);
            shader->setMat4("model", model);
            shader->setMat4("view", view);
            shader->setMat4("projection", projection);



            // textureWhite->use();
            atlas->use();
            // textureWolf->use();

            world.render();






            // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
            glfwSwapBuffers(p_win);
            glfwPollEvents();
        }

        // // not necessary
        // chunk.delete_data();
        // chunk2.delete_data();
    }



private:

    inline static bool ePressed = false;
    // prcess all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
    static void proccessInput(GLFWwindow* window)
    {
        // uncapture mouse cursor
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
                glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

        // camera movement
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            camera.ProcessKeyboard(FORWARD, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            camera.ProcessKeyboard(BACKWARD, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            camera.ProcessKeyboard(LEFT_c, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            camera.ProcessKeyboard(RIGHT_c, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
            camera.ProcessKeyboard(UP, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
            camera.ProcessKeyboard(DOWN, deltaTime);

        if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
            camera.ProcessKeyboard(SPRINT, deltaTime);

        // wireframe toggle
        bool eCurrentlyPressed = glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS;
        if (eCurrentlyPressed && !ePressed) { // only true on first keypress
            wireframe = !wireframe;
        }
        ePressed = eCurrentlyPressed;
    }

    // glfw: whenever the window size changed (by OS or user resize) this callback function executes
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height)
    {
        glViewport(0, 0, width, height);
    }

    // glfw: whenever the mouse moves, this callback is called (mouse movement)
    static void mouse_callback(GLFWwindow* window, double xposIn, double yposIn) {
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

    // glfw: whenever the mouse scroll wheel scrolls, this callback is called
    static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
    {
        camera.ProcessMouseScroll(static_cast<float>(yoffset));
    }




};



#endif