#ifndef TEXTURE_H
#define TEXTURE_H

#include "includes/glad.h"
#include "includes/glfw3.h"

#define STB_IMAGE_IMPLEMENTATION
#include "includes/stb_image.h"

#include "includes/glm/glm.hpp"
#include "includes/glm/gtc/matrix_transform.hpp"
#include "includes/glm/gtc/type_ptr.hpp"

#include "shader.h"
#include "camera.h"
#include "block.h"

#include <iostream>
#include <cmath>

// class to apply textures to single block

class Texture
{
public:
    unsigned int texture;
    Texture(const char* path)
    {
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        // set the texture wrapping/filtering options (on the currently bound texture object)
        // set texture wrapping to GL_REPEAT (default wrapping method)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
        // set texture filtering parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);	// set texture filtering to nearest neighbor
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);	// set texture filtering to nearest neighbor

        // load and generate the texture
        // stbi_set_flip_vertically_on_load(true); // flip loaded texture on y-axis
        int width, height, nrChannels;
        unsigned char* data = stbi_load(path, &width, &height, &nrChannels, 0);
        if (data)
        {
            // generate texture
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);	// generate texture
            glGenerateMipmap(GL_TEXTURE_2D);	// generate mipmaps
        }
        else
        {
            std::cout << "Failed to load texture" << std::endl;
        }
        stbi_image_free(data);	// free image memory

        Shader shader("shaders/vertex.shader", "shaders/fragment.shader");
        shader.use();
        // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
        shader.setInt("texture1", 0);
    }
    ~Texture()
    {
        glDeleteTextures(1, &texture);
    }

    void use()
    {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);
    }
};







#endif