#include "includes/glad.h"
#include "includes/glfw3.h"

#include <iostream>


void framebuffer_size_callback(GLFWwindow* window, int width, int height);  // definition unten
void processInput(GLFWwindow *window);

// --- settings ---
const unsigned int SCR_HEIGHT = 800;
const unsigned int SCR_WIDTH = 600;

const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";
const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(0.6f, 0.6f, 1.0f, 1.0f);\n"
    "}\n\0";


int main()
{
    /* --- glfw: initialize and configure --- */
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // macos only

    /* --- glfw window creation --- */
    GLFWwindow* window = glfwCreateWindow(SCR_HEIGHT, SCR_WIDTH, "meincraft", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    /* --- glad: load all OpenGL function pointers --- */
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    /* --- shaders --- */
    // vertex shader
        unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER); // create vertex shader object
        glShaderSource(vertexShader, 1, &vertexShaderSource, NULL); // attach shader source code to shader object
        glCompileShader(vertexShader); // compile shader
        // check for compile errors
        int success;       // is reused
        char infoLog[512]; // is reused
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success); // check for compile errors
        if (!success)
        {
            glGetShaderInfoLog(vertexShader, 512, NULL, infoLog); // get error message
            std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        }

    // fragment shader
        unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER); // create fragment shader object
        glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL); // attach shader source code to shader object
        glCompileShader(fragmentShader); // compile shader
        // check for compile errors
        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success); // check for compile errors
        if (!success)
        {
            glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog); // get error message
            std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
        }

    // shader program (link shaders)
        unsigned int shaderProgram = glCreateProgram(); // create shader program object
        glAttachShader(shaderProgram, vertexShader); // attach vertex shader to shader program
        glAttachShader(shaderProgram, fragmentShader); // attach fragment shader to shader program
        glLinkProgram(shaderProgram); // link shader program
        // check for linking errors
        glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success); // check for linking errors
        if (!success)
        {
            glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog); // get error message
            std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        }
        glDeleteShader(vertexShader);   // delete shader objects, they are no longer needed
        glDeleteShader(fragmentShader); // --



    float vertices[] = {
        // bottom right
        -0.5f, -0.5f, 0.0f, // left
         0.5f, -0.5f, 0.0f, // right
         0.5f,  0.5f, 0.0f, // top
        // top left
        -0.5f,  0.5f, 0.0f, // left
         0.5f,  0.5f, 0.0f, // right
        -0.5f, -0.5f, 0.0f  // bottom
    };

    /* --- linking vertex attributes --- */
    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO); // generate vertex array object names
    glGenBuffers(1, &VBO);      // generate buffer object names

    /* 1. bind the Vertex Array Object first */
    glBindVertexArray(VAO);

    /* 2. then bind and set vertex buffer */
    glBindBuffer(GL_ARRAY_BUFFER, VBO); // bind buffer to target (GL_ARRAY_BUFFER)
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // copy defined vertex data into buffer's memory

    /* 3. and then configure vertex attributes (specify how OpenGL should interpret the vertex data before rendering) */
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0); // specify
    glEnableVertexAttribArray(0); // enable vertex attribute


    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0);






    // uncomment this call to draw in wireframe polygons.
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

/* ------------------------------------------------------------------------------------------------------- */
/* --------------------------------------------- render loop --------------------------------------------- */

    while (!glfwWindowShouldClose(window))
    {
        processInput(window); // input


        /* --- rendering commands --- */

            glClearColor(0.0f, 0.0f, 0.1f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            // draw triangle
            glUseProgram(shaderProgram); // use shader program
            glBindVertexArray(VAO); // bind vertex array object
            glDrawArrays(GL_TRIANGLES, 0, 6); // draw triangles
            // glBindVertexArray(0); // no need to unbind it every time

        /* --- rendering commands --- */


        glfwSwapBuffers(window); // swap buffers
        glfwPollEvents();        // poll IO events (keys pressed/released, mouse moved etc.)
    }

/* --------------------------------------------- render loop --------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------- */


    glfwTerminate();
    return 0;
}



// glfw: whenever the window size changed (by OS or user resize) this callback function executes
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height); // make sure the viewport matches the new window dimensions

    std::cout << "window resized to " << width << "x" << height << std::endl;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true); // close window with ESC
    }

}