#ifndef NEWCHUNK_H
#define NEWCHUNK_H

#include "../settings.h"
#include "../../includes/FastNoiseLite.h"
#include "block.h"

#include "../Graphics/VAO.h"
#include "../Graphics/VBO.h"
#include "../Graphics/EBO.h"



class NEWChunk
{
public: // TODO: make private
    // VAO *vao;
    VBO *vbo;
    VBO *vbo_texture;
    EBO *ebo;

    std::vector<glm::vec3> chunkVertexData = {};
    std::vector<float> chunkTextureData = {};
    std::vector<int> chunkIndices = {};

    std::vector<glm::vec3> leftBorder = {};
    std::vector<glm::vec3> rightBorder = {};
    std::vector<glm::vec3> frontBorder = {};
    std::vector<glm::vec3> backBorder = {};

    static constexpr int chunkSize = 32;
    static constexpr int chunkHeight = 128;
    // ziel: 32 x 128 x 32

    int indices_amount = 0;
    int faces_amount = 0;

    Block *block;
    Block *blockStorage_a[chunkSize][chunkHeight][chunkSize];

    FastNoiseLite noise;
    int noiseHeight;

public:
    glm::vec3 chunkPosition;

    NEWChunk(glm::vec3 position, VAO vao)
        : chunkPosition(position)
    {
        // minecraft noise
        noise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
        noise.SetFractalType(FastNoiseLite::FractalType_FBm);
        noise.SetFractalOctaves(6);
        noise.SetFrequency(0.01f);
        noise.SetFractalLacunarity(2.0f);
        noise.SetFractalGain(0.5f);


        generate_Blocks();

        pick_Faces();

        build_Chunk(vao);
    }




    // terrain generation
    void calculate_NoiseHeight(int x, int z)
    {
        noiseHeight = noise.GetNoise((chunkPosition.x+x)/10, (chunkPosition.z+z)/10) * 300 + 5; // bei chunkHeight 128 bis zu *800 (*400 reicht)
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
                        if (y == noiseHeight -1) block = new Block(chunkPosition + glm::vec3(x, y, z), BlockType::GRASS);
                        else if (y > noiseHeight -6) block = new Block(chunkPosition + glm::vec3(x, y, z), BlockType::DIRT);
                        else block = new Block(chunkPosition + glm::vec3(x, y, z), BlockType::STONE);

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
                    else add_Face(*blockStorage_a[x][y][z], Faces::LEFT); // furthest left is always added
                    // right face (when block to the right is empty)
                    if (x<chunkSize-1)
                    {
                        if (blockStorage_a[x+1][y][z]->type == BlockType::EMPTY)
                        {
                            add_Face(*blockStorage_a[x][y][z], Faces::RIGHT);
                        }
                    }
                    else add_Face(*blockStorage_a[x][y][z], Faces::RIGHT); // furthest right is always added

                    // top face (when block above is empty)
                    if (y<noiseHeight-1) // terrain generation
                    {
                        if (blockStorage_a[x][y+1][z]->type == BlockType::EMPTY)
                        {
                            add_Face(*blockStorage_a[x][y][z], Faces::TOP);
                        }
                    }
                    else add_Face(*blockStorage_a[x][y][z], Faces::TOP); // top is always added
                    // bottom face (when block below is empty)
                    if (y>0)
                    {
                        if (blockStorage_a[x][y-1][z]->type == BlockType::EMPTY)
                        {
                            add_Face(*blockStorage_a[x][y][z], Faces::BOTTOM);
                        }
                    }
                    else add_Face(*blockStorage_a[x][y][z], Faces::BOTTOM); // bottom is always added

                    // front face (when block in front is empty)
                    if (z<chunkSize-1)
                    {
                        if (blockStorage_a[x][y][z+1]->type == BlockType::EMPTY)
                        {
                            add_Face(*blockStorage_a[x][y][z], Faces::FRONT);
                        }
                    }
                    else  add_Face(*blockStorage_a[x][y][z], Faces::FRONT); // front is always added
                    // back face (when block behind is empty)
                    if (z>0)
                    {
                        if (blockStorage_a[x][y][z-1]->type == BlockType::EMPTY)
                        {
                            add_Face(*blockStorage_a[x][y][z], Faces::BACK);
                        }
                    }
                    else add_Face(*blockStorage_a[x][y][z], Faces::BACK); // back is always added
                    // --- culling culling culling culling culling culling culling ---

                    generate_Indices(faces_amount);
                }
            }
        }
        std::cout << "Faces picked" << std::endl;
    }



    void add_Face(Block block, Faces face) // problem: using last chunks chunkTextureData for every chunk
    {

        // TODO: if block is on border, add block to vector of border blocks, later compare chunks according to neighboring borders and dont add faces of border blocks that are not visible
        // => have to do all of this outside of a single chunks class and somewhere where multiple chunks members can be compared

        // Get the block's local coordinates within the chunk
        int x = static_cast<int>(block.blockPosition.x - chunkPosition.x);
        int y = static_cast<int>(block.blockPosition.y - chunkPosition.y);
        int z = static_cast<int>(block.blockPosition.z - chunkPosition.z);

        // Check if the block is on the border of the chunk
        bool isOnLeftBorder = (x == 0);
        bool isOnRightBorder = (x == chunkSize - 1);
        // bool isOnBottomBorder = (y == 0);
        // bool isOnTopBorder = (y == chunkHeight - 1);
        bool isOnFrontBorder = (z == 0);
        bool isOnBackBorder = (z == chunkSize - 1);



        std::vector<glm::vec3> faceVertexData = block.getFace(face); // default
        if (isOnLeftBorder && face == Faces::LEFT)
        {
            // translate local block coordinates to world coordinates
            for (glm::vec3& vertex : faceVertexData)
            {
                vertex += chunkPosition;
            }
            // add to chunks left border vector
            leftBorder.insert(leftBorder.end(), faceVertexData.begin(), faceVertexData.end());
            return;
        }
        if (isOnRightBorder && face == Faces::RIGHT)
        {
            // translate local block coordinates to world coordinates
            for (glm::vec3& vertex : faceVertexData)
            {
                vertex += chunkPosition;
            }
            // add to chunks right border vector
            rightBorder.insert(rightBorder.end(), faceVertexData.begin(), faceVertexData.end());
            return;
        }
        if (isOnFrontBorder && face == Faces::FRONT)
        {
            // translate local block coordinates to world coordinates
            for (glm::vec3& vertex : faceVertexData)
            {
                vertex += chunkPosition;
            }
            // add to chunks front border vector
            frontBorder.insert(frontBorder.end(), faceVertexData.begin(), faceVertexData.end());
            return;
        }
        if (isOnBackBorder && face == Faces::BACK)
        {
            // translate local block coordinates to world coordinates
            for (glm::vec3& vertex : faceVertexData)
            {
                vertex += chunkPosition;
            }
            // add to chunks back border vector
            backBorder.insert(backBorder.end(), faceVertexData.begin(), faceVertexData.end());
            return;
        }



        chunkVertexData.insert(chunkVertexData.end(), faceVertexData.begin(), faceVertexData.end()); // default // DO THIS AFTER COMPARING CHUNK BORDERS






        // temporary grass texture data // TODO: implement properly
        if (block.type == BlockType::GRASS)
        {
            if (face == Faces::TOP) block.type = BlockType::GRASS_TOP;
            else if (face == Faces::BOTTOM) block.type = BlockType::DIRT;
            else block.type = BlockType::GRASS;
        }

        std::vector<float> faceTextureData = block.getTexture(block.type);
        chunkTextureData.insert(chunkTextureData.end(), faceTextureData.begin(), faceTextureData.end());

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






    void build_Chunk(VAO &vao) // render pipeline
    {
        // vao = new VAO();
        vbo = new VBO(chunkVertexData, chunkTextureData, vao);
        ebo = new EBO(chunkIndices);
    }
    void render_Chunk(VAO &vao) // normal
    {
        vbo->bindVBO();
        vao.linktoVBO(0, 3); // vertex data // has to be done every frame because chunks have different positions
        vbo->createTextureVBO(chunkTextureData, vao);

        // glBindVertexArray(vao.m_ID); // bind the vertex array object // can now be done in render_World()
        // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo->m_ID); // ??? works without ??? // bind the buffer to the GL_ELEMENT_ARRAY_BUFFER target
        glDrawElements(GL_TRIANGLES, static_cast<int>(chunkIndices.size()), GL_UNSIGNED_INT, 0); // draw the rectangle

        vbo->unbindVBO();

    }


};

#endif