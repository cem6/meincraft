#ifndef CHUNK_H
#define CHUNK_H

#include "../settings.h"
#include "../../includes/FastNoiseLite.h"
#include "block.h"

#include "../Graphics/VAO.h"
#include "../Graphics/VBO.h"
#include "../Graphics/EBO.h"



class Chunk
{
public: // TODO: make private
    VAO *vao;
    VBO *vbo;
    VBO *vbo_texture;
    EBO *ebo;

    std::vector<glm::vec3> chunkVertexData = {};
    std::vector<float> chunkTextureData = {};
    std::vector<int> chunkIndices = {};

    static constexpr int chunkSize = 16;
    static constexpr int chunkHeight = 320;
    // ziel: 32 x 320 x 32

    int indices_amount = 0;
    int faces_amount = 0;

    Block *block;
    Block *blockStorage_a[chunkSize][chunkHeight][chunkSize];

    FastNoiseLite noise;
    int noiseHeight;

public:
    glm::vec3 chunkPosition;

    Chunk(glm::vec3 position)
        : chunkPosition(position)
    {
        // noise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);
        // noise.SetFractalType(FastNoiseLite::FractalType_FBm);
        // noise.SetFractalOctaves(4);
        // noise.SetFrequency(0.01f);
        // noise.SetFractalLacunarity(2.0f);
        // noise.SetFractalGain(0.5f);

        // generate_Blocks();
        generate_Blocks();

        pick_Faces();

        build_Chunk();
    }



    void calculate_NoiseHeight(int x, int z)
    {
        noiseHeight = noise.GetNoise((chunkPosition.x+x)/10, (chunkPosition.z+z)/10) * 200 + 0;
    }
    // new (terrain generation)
    void generate_Blocks() // add blocks to storage
    {
        for (int x=0; x<chunkSize; x++)
        {
            for (int z=0; z<chunkSize; z++)
            {
                calculate_NoiseHeight(x, z);
                for (int y=0; y<chunkHeight; y++)
                {

                    if (y < noiseHeight) // terrain generation
                    {
                        block = new Block(chunkPosition + glm::vec3(x, y, z), BlockType::DIRT);
                        blockStorage_a[x][y][z] = block;
                    }
                    else
                    {
                        block = new Block(chunkPosition + glm::vec3(x, y, z), BlockType::EMPTY);
                        blockStorage_a[x][y][z] = block;
                    }

                }
            }
            // std::cout << x << std::endl;
        }
        std::cout << "Chunk created" << std::endl;
    }

    void pick_Faces() // pick faces to render appropriate to blocks in storage
    {
        for (int x=0; x<chunkSize; x++)
        {
            for (int z=0; z<chunkSize; z++)
            {
                calculate_NoiseHeight(x, z);
                for (int y=0; y<noiseHeight; y++) // terrain generation
                {
                    faces_amount = 0;

                    // --- culling culling culling culling culling culling culling ---
                    // left face (when block to the left is empty)
                    if (x>0)
                    {
                        if (blockStorage_a[x-1][y][z]->type == BlockType::EMPTY)
                        {
                            add_Face(*blockStorage_a[x][y][z], Faces::LEFT);
                        }
                    }
                    else // furthest left is always added
                    {
                        add_Face(*blockStorage_a[x][y][z], Faces::LEFT);
                    }
                    // right face (when block to the right is empty)
                    if (x<chunkSize-1)
                    {
                        if (blockStorage_a[x+1][y][z]->type == BlockType::EMPTY)
                        {
                            add_Face(*blockStorage_a[x][y][z], Faces::RIGHT);
                        }
                    }
                    else // furthest right is always added
                    {
                        add_Face(*blockStorage_a[x][y][z], Faces::RIGHT);
                    }

                    // top face (when block above is empty)
                    if (y<noiseHeight-1) // terrain generation
                    {
                        if (blockStorage_a[x][y+1][z]->type == BlockType::EMPTY)
                        {
                            add_Face(*blockStorage_a[x][y][z], Faces::TOP);
                        }
                    }
                    else // top is always added
                    {
                        add_Face(*blockStorage_a[x][y][z], Faces::TOP);
                    }
                    // bottom face (when block below is empty)
                    if (y>0)
                    {
                        if (blockStorage_a[x][y-1][z]->type == BlockType::EMPTY)
                        {
                            add_Face(*blockStorage_a[x][y][z], Faces::BOTTOM);
                        }
                    }
                    else // bottom is always added
                    {
                        add_Face(*blockStorage_a[x][y][z], Faces::BOTTOM);
                    }

                    // front face (when block in front is empty)
                    if (z<chunkSize-1)
                    {
                        if (blockStorage_a[x][y][z+1]->type == BlockType::EMPTY)
                        {
                            add_Face(*blockStorage_a[x][y][z], Faces::FRONT);
                        }
                    }
                    else // front is always added
                    {
                        add_Face(*blockStorage_a[x][y][z], Faces::FRONT);
                    }
                    // back face (when block behind is empty)
                    if (z>0)
                    {
                        if (blockStorage_a[x][y][z-1]->type == BlockType::EMPTY)
                        {
                            add_Face(*blockStorage_a[x][y][z], Faces::BACK);
                        }
                    }
                    else // back is always added
                    {
                        add_Face(*blockStorage_a[x][y][z], Faces::BACK);
                    }
                    // --- culling culling culling culling culling culling culling ---

                    generate_Indices(faces_amount);
                }
            }
        }
        std::cout << "Faces picked" << std::endl;
    }

    void add_Face(Block block, Faces face)
    {
        // vertex data
        std::vector<glm::vec3> faceVertexData = block.getFace(face);
        chunkVertexData.insert(chunkVertexData.end(), faceVertexData.begin(), faceVertexData.end());

        // texture data
        chunkTextureData.insert(chunkTextureData.end(), textureData.begin(), textureData.end()); // i think the orientation is wrong

        faces_amount++; // ++ for every face, later used for indices
    }

    void generate_Indices(int faces_amount)
    {
        for (int i=0; i<faces_amount; i++)
         {
             chunkIndices.push_back(indices_amount + 0);
             chunkIndices.push_back(indices_amount + 1);
             chunkIndices.push_back(indices_amount + 2);

             chunkIndices.push_back(indices_amount + 2);
             chunkIndices.push_back(indices_amount + 3);
             chunkIndices.push_back(indices_amount + 0);

             indices_amount += 4;
         }
    }






    void build_Chunk() // render pipeline
    {
        vao = new VAO();
        vbo = new VBO(chunkVertexData, chunkTextureData, *vao);
        ebo = new EBO(chunkIndices);
    }
    void render_Chunk() // normal
    {
        std::cout << "rendering chunk " << vao->m_ID << std::endl;
        glBindVertexArray(vao->m_ID); // bind the vertex array object
        // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo->m_ID); // ??? works without ??? // bind the buffer to the GL_ELEMENT_ARRAY_BUFFER target
        glDrawElements(GL_TRIANGLES, static_cast<int>(chunkIndices.size()), GL_UNSIGNED_INT, 0); // draw the rectangle
    }

    // void render_Chunk() // debug
    // {
    //     std::cout << "rendering chunk " << std::endl;
    //
    //     // error check
    //     GLenum error = glGetError();
    //     if (error != GL_NO_ERROR)
    //     {
    //         std::cout << "OpenGL Error: " << error << std::endl;
    //     }
    //
    //     std::cout << "vao: " << vao->m_ID << std::endl; // TODO: fix (cant access vao->m_ID)
    //     glBindVertexArray(vao->m_ID); // bind the vertex array object
    //     std::cout << "vao bound" << std::endl;
    //
    //     std::cout << "ebo: " << ebo->m_ID << std::endl; // TODO: fix (cant access ebo->m_ID)
    //     glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo->m_ID); // ??? works without ??? // bind the buffer to the GL_ELEMENT_ARRAY_BUFFER target
    //     std::cout << "ebo bound" << std::endl;
    //
    //     glDrawElements(GL_TRIANGLES, static_cast<int>(chunkIndices.size()), GL_UNSIGNED_INT, nullptr); // draw the rectangle
    //     std::cout << "elements drawn\n---" << std::endl;
    // }


/* ---------------------------------------- RENDER PIPELINE HARDCODED ---------------------------------------- */
    // unsigned int VAO_HARD, VBO_HARD, texture_VBO_HARD, EBO_HARD;
    // void build_Chunk() // DEBUG HAAAAARRRDDD
    // {
    //     glGenVertexArrays(1, &VAO_HARD);
    //     glBindVertexArray(VAO_HARD);
    //     std::cout << "VAO: " << VAO_HARD << std::endl;
    //
    //     glGenBuffers(1, &VBO_HARD);
    //     glGenBuffers(1, &texture_VBO_HARD);
    //     // vertex data
    //     glBindBuffer(GL_ARRAY_BUFFER, VBO_HARD);
    //     glBufferData(GL_ARRAY_BUFFER, chunkVertexData.size() * sizeof(glm::vec3), &chunkVertexData[0], GL_STATIC_DRAW);
    //     // link
    //     glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    //     glEnableVertexAttribArray(0);
    //     std::cout << "VBO: " << VBO_HARD << std::endl;
    //     // texture data
    //     glBindBuffer(GL_ARRAY_BUFFER, texture_VBO_HARD);
    //     glBufferData(GL_ARRAY_BUFFER, chunkTextureData.size() * sizeof(float), &chunkTextureData[0], GL_STATIC_DRAW);
    //     // link
    //     glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
    //     glEnableVertexAttribArray(1);
    //     std::cout << "texture VBO: " << texture_VBO_HARD << std::endl;
    //
    //     glGenBuffers(1, &EBO_HARD);
    //     glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_HARD);
    //     glBufferData(GL_ELEMENT_ARRAY_BUFFER, chunkIndices.size() * sizeof(int), &chunkIndices[0], GL_STATIC_DRAW);
    //     std::cout << "EBO: " << EBO_HARD << std::endl;
    //     std::cout << "Chunk built" << std::endl;
    // }
    // void render_Chunk() // DEBUG HAAAAARRRDDD
    // {
    //     std::cout << "rendering chunk " << std::endl;
    //
    //     // error check
    //     GLenum error = glGetError();
    //     if (error != GL_NO_ERROR)
    //     {
    //         std::cout << "OpenGL Error: " << error << std::endl;
    //     }
    //
    //     std::cout << "vao: " << VAO_HARD << std::endl; // TODO: fix (cant access vao->m_ID)
    //     glBindVertexArray(VAO_HARD); // bind the vertex array object
    //     std::cout << "vao bound" << std::endl;
    //
    //     std::cout << "ebo: " << EBO_HARD << std::endl; // TODO: fix (cant access ebo->m_ID)
    //     glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_HARD); // ??? works without ??? // bind the buffer to the GL_ELEMENT_ARRAY_BUFFER target
    //     std::cout << "ebo bound" << std::endl;
    //
    //     glDrawElements(GL_TRIANGLES, static_cast<int>(chunkIndices.size()), GL_UNSIGNED_INT, nullptr); // draw the rectangle
    //     std::cout << "chunk drawn\n---" << std::endl;
    // }
/* ---------------------------------------- RENDER PIPELINE HARDCODED ---------------------------------------- */


    // not necessary
    void delete_data() const
    {
        glDeleteVertexArrays(1, &vao->m_ID);
        glDeleteBuffers(1, &vbo->m_ID);
        glDeleteBuffers(1, &vbo_texture->m_ID);
        glDeleteBuffers(1, &ebo->m_ID);
    }

};

#endif