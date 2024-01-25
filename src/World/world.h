#ifndef WORLD_H
#define WORLD_H

#include "../settings.h"
// #include "chunk.h"
#include "NEWchunk.h"
#include "../Graphics/VAO.h"



class World
{
public:
    VAO *vao;
    static constexpr int s = 2; // procedural generation: always 16x16 chunks
    static constexpr int s_half = s/2;
    NEWChunk *chunkStorage[s][s];

    World()
    {
        vao = new VAO();
        generate_World();
    }

    void generate_World()
    {
        for (int x=0; x<s; x++)
        {
            for (int z=0; z<s; z++)
            {
                chunkStorage[x][z] = new NEWChunk(glm::vec3(32*x, 0, 32*z), *vao);
            }
        }
    }

    void render()
    {
        glBindVertexArray(vao->m_ID);
        for (int x=0; x<s; x++)
        {
            for (int z=0; z<s; z++)
            {
                chunkStorage[x][z]->render_Chunk(*vao);
            }
        }
    }



};


#endif