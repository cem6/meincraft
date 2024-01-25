#ifndef TEXTURE_H
#define TEXTURE_H

#include "settings.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../includes/stb_image.h"



#include <iostream>
#include <string>


class Texture
{
public:

    unsigned int texture1;

    Texture(const char* texturePath)
    {
        setup(texturePath);
        std::cout << "Texture created" << std::endl;
    }

    ~Texture()
    {
        std::cout << "Texture destroyed" << std::endl;
        glDeleteTextures(1, &texture1);
    }

    void use()
    {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        // std::cout << "Texture used" << std::endl;
    }

private:
    void setup(const char* texturePath)
    {
        glGenTextures(1, &texture1);
        glBindTexture(GL_TEXTURE_2D, texture1);
        // set the texture wrapping/filtering options (on the currently bound texture object)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);	// set texture filtering to nearest neighbor
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);	// set texture filtering to nearest neighbor

        // load and generate the texture
        stbi_set_flip_vertically_on_load(true); // flip loaded texture on y-axis
        int width, height, nrChannels;
        unsigned char* data = stbi_load(texturePath, &width, &height, &nrChannels, 0);
        if (data)
        {
            // generate texture
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);	// generate mipmaps
        }
        else
        {
            std::cout << "Failed to load texture1" << std::endl;
        }
        stbi_image_free(data);	// free image memory
    }

};




#endif


