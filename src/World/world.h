#ifndef WORLD_H
#define WORLD_H

#include "../settings.h"

#include "chunk.h"
#include "../Graphics/VAO.h"

#include <list>



class World
{
public:
    VAO *vao;
    static constexpr int s = 2; // procedural generation: always 8x8 chunks
    static constexpr int s_half = s/2;
    std::list<NEWChunk> chunkList;  // Using std::list instead of std::set
    NEWChunk *chunk;

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
                chunk = new NEWChunk(glm::vec3(32*x, 0, 32*z), *vao);
                chunkList.push_back(*chunk);
            }
        }
    }

    void render()
    {
        glBindVertexArray(vao->m_ID);

        for (NEWChunk& chunk : chunkList)
        {
            chunk.render_Chunk(*vao);
        }
    }

    void load_Chunk(const glm::vec3 &cameraPosition)
    {
        // player position in chunk coordinates
        int xPos = (int)cameraPosition.x / 32;
        int zPos = (int)cameraPosition.z / 32;


    }


    // // add chunks to chunkList
    // for (int x = xPos-s_half; x <= xPos+s_half; x++)
    // {
    //     for (int z = zPos-s_half; z <= zPos+s_half; z++)
    //     {
    //         // check if chunk is in chunkList
    //         bool chunkInList = false;
    //         for (NEWChunk& chunk : chunkList)
    //         {
    //             if (chunk.position.x == x*32 && chunk.position.z == z*32)
    //             {
    //                 chunkInList = true;
    //                 break;
    //             }
    //         }
    //         // if chunk is not in chunkList, add it
    //         if (!chunkInList)
    //         {
    //             chunk = new NEWChunk(glm::vec3(32*x, 0, 32*z), *vao);
    //             chunkList.push_back(*chunk);
    //         }
    //     }
    // }




};


#endif