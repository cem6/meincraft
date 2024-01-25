#ifndef EBO_H
#define EBO_H

#include "../settings.h"

#include <vector>
#include <iostream>

class EBO
{
public:
    unsigned int m_ID; // can be private

    EBO(const std::vector<int> &data)
    {
        glGenBuffers(1, &m_ID); // indices

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, data.size() * sizeof(int), &data[0], GL_STATIC_DRAW);

        std::cout << "EBO created with ID: " << m_ID << "\n---" << std::endl;
    }

    void bindEBO () { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID); }
    void unbindEBO () { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }
    void deleteEBO () { glDeleteBuffers(1, &m_ID); }

};



#endif