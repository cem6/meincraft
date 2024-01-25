#ifndef VBO_H
#define VBO_H

#include "../settings.h"
#include "VAO.h"

#include <vector>
#include <iostream>


class VBO
{
public:
    unsigned int m_ID; // can be private
    unsigned int m_ID_texture; // can be private

    VBO (const std::vector<glm::vec3> &vertex_data, const std::vector<float> &texture_data, VAO vao)
    {
        glGenBuffers(1, &m_ID); // vertex data
        glGenBuffers(1, &m_ID_texture); // texture data // has to be bound every time a different texture is drawn => own function

        // bind vertex data
        glBindBuffer(GL_ARRAY_BUFFER, m_ID);
        glBufferData(GL_ARRAY_BUFFER, vertex_data.size() * sizeof(glm::vec3), &vertex_data[0], GL_STATIC_DRAW);

        vao.linktoVBO(0, 3); // vertex data


        std::cout << "vertex VBO created with ID: " << m_ID << std::endl;
        std::cout << "texture VBO created with ID: " << m_ID_texture << std::endl;
    }

    void createTextureVBO (const std::vector<float> &texture_data, VAO vao)
    {
        // bind texture data, every face has different texture coordinates
        glBindBuffer(GL_ARRAY_BUFFER, m_ID_texture);
        glBufferData(GL_ARRAY_BUFFER, texture_data.size() * sizeof(float), &texture_data[0], GL_STATIC_DRAW);

        vao.linktoVBO(1, 2); // texture data
    }

    void bindVBO () { glBindBuffer(GL_ARRAY_BUFFER, m_ID); }
    void unbindVBO () { glBindBuffer(GL_ARRAY_BUFFER, 0); }
    void deleteVBO () { glDeleteBuffers(1, &m_ID); }

private:



};



#endif