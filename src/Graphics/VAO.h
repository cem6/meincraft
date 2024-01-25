#ifndef VAO_H
#define VAO_H

#include "../settings.h"

#include "VBO.h"

#include <iostream>


class VAO
{
public:
    unsigned int m_ID; // can be private
    friend class Chunk;
    friend class World;

    VAO ()
    {
        // generate vao
        glGenVertexArrays(1, &m_ID);
        glBindVertexArray(m_ID);

        std::cout << "---\n" <<"VAO created with ID: " << m_ID << std::endl;
    }

    ~VAO ()
    {
        // unbindVAO();
        // std::cout << "VAO with ID: " << m_ID << " unbinded" << std::endl;
    }

    void bindVAO () { glBindVertexArray(m_ID); }
    void unbindVAO () { glBindVertexArray(0); }
    void deleteVAO () { glDeleteVertexArrays(1, &m_ID); }


    void linktoVBO(int location, int size) // is used in VBO.h
    {
        glVertexAttribPointer(location, size, GL_FLOAT, GL_FALSE, 0, (void*)0);
        glEnableVertexAttribArray(location);
    }

};



#endif