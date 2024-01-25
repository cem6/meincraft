#ifndef SETTINGS_H
#define SETTINGS_H

#include "../includes/glm/glm.hpp"
#include "../includes/glm/gtc/matrix_transform.hpp"
#include "../includes/glm/gtc/type_ptr.hpp"

#include "../includes/glad.h"
#include "../includes/glfw3.h"

#include "shader.h"

#include <string>
#include <vector>




// window settings
// inline int g_width = 800;   // 4:3
// inline int g_height = 600;
inline int g_width = 1152;  // 16:9
inline int g_height = 648;
inline GLFWwindow *p_win;

// camera settings
inline float lastX = g_width / 2.0f;
inline float lastY = g_height / 2.0f;
inline bool firstMouse = true;

// time
inline float deltaTime = 0.0f;	// Time between current frame and last frame
inline float lastFrame = 0.0f;  // Time of last frame

// render
inline bool wireframe = false;

    // inline std::vector<glm::vec3> vertex_data = {
    //     // every single face, weil irgendwann textures
    //     // front
    //     glm::vec3(-0.5f,  0.5f, 0.5f), // top left 0
    //     glm::vec3( 0.5f,  0.5f, 0.5f), // top right 1
    //     glm::vec3( 0.5f, -0.5f, 0.5f), //  bottom right 2
    //     glm::vec3(-0.5f, -0.5f, 0.5f), // bottom left 3
    //     // back
    //     glm::vec3(-0.5f,  0.5f, -0.5f), // top left 0
    //     glm::vec3( 0.5f,  0.5f, -0.5f), // top right 1
    //     glm::vec3( 0.5f, -0.5f, -0.5f), //  bottom right 2
    //     glm::vec3(-0.5f, -0.5f, -0.5f), // bottom left 3
    //     // left
    //     glm::vec3(-0.5f,  0.5f, -0.5f), // top left 0
    //     glm::vec3(-0.5f,  0.5f,  0.5f), // top right 1
    //     glm::vec3(-0.5f, -0.5f,  0.5f), //  bottom right 2
    //     glm::vec3(-0.5f, -0.5f, -0.5f), // bottom left 3
    //     // right
    //     glm::vec3( 0.5f,  0.5f, -0.5f), // top left 0
    //     glm::vec3( 0.5f,  0.5f,  0.5f), // top right 1
    //     glm::vec3( 0.5f, -0.5f,  0.5f), //  bottom right 2
    //     glm::vec3( 0.5f, -0.5f, -0.5f), // bottom left 3
    //     // top
    //     glm::vec3(-0.5f,  0.5f, -0.5f), // top left 0
    //     glm::vec3( 0.5f,  0.5f, -0.5f), // top right 1
    //     glm::vec3( 0.5f,  0.5f,  0.5f), //  bottom right 2
    //     glm::vec3(-0.5f,  0.5f,  0.5f), // bottom left 3
    //     // bottom
    //     glm::vec3(-0.5f, -0.5f, -0.5f), // top left 0
    //     glm::vec3( 0.5f, -0.5f, -0.5f), // top right 1
    //     glm::vec3( 0.5f, -0.5f,  0.5f), //  bottom right 2
    //     glm::vec3(-0.5f, -0.5f,  0.5f), // bottom left 3
    // };
    //
    // inline std::vector<int> indices = {
    //     // front
    //     0, 1, 2, // top left 0 -> top right 1 -> bottom right 2
    //     0, 2, 3, // top left 0 -> bottom right 2 -> bottom left 3
    //     // back
    //     4, 5, 6, // top left 0 -> top right 1 -> bottom right 2
    //     4, 6, 7, // top left 0 -> bottom right 2 -> bottom left 3
    //     // left
    //     8, 9, 10, // top left 0 -> top right 1 -> bottom right 2
    //     8, 10, 11, // top left 0 -> bottom right 2 -> bottom left 3
    //     // right
    //     12, 13, 14, // top left 0 -> top right 1 -> bottom right 2
    //     12, 14, 15, // top left 0 -> bottom right 2 -> bottom left 3
    //     // top
    //     16, 17, 18, // top left 0 -> top right 1 -> bottom right 2
    //     16, 18, 19, // top left 0 -> bottom right 2 -> bottom left 3
    //     // bottom
    //     20, 21, 22, // top left 0 -> top right 1 -> bottom right 2
    //     20, 22, 23, // top left 0 -> bottom right 2 -> bottom left 3
    // };


#endif // !SETTINGS_H