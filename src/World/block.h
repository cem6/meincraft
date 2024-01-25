#ifndef BLOCK_H
#define BLOCK_H

#include "../settings.h"

#include <unordered_map>
#include <vector>


enum BlockType
{
    EMPTY,
    DIRT, // == GRASS_BOTTOM
    GRASS_TOP,
    GRASS, // == GRASS_SIDE
    STONE,
};


enum Faces
{
    FRONT,
    BACK,
    LEFT,
    RIGHT,
    TOP,
    BOTTOM
};


inline static std::unordered_map<Faces, std::vector<glm::vec3>> rawVertexData = {
    { FRONT, {
        glm::vec3(-0.5f,  0.5f, 0.5f), // top left 0
        glm::vec3( 0.5f,  0.5f, 0.5f), // top right 1
        glm::vec3( 0.5f, -0.5f, 0.5f), // bottom right 2
        glm::vec3(-0.5f, -0.5f, 0.5f), // bottom left 3
    } },
    { BACK, {
        glm::vec3(-0.5f,  0.5f, -0.5f), // top left 0
        glm::vec3( 0.5f,  0.5f, -0.5f), // top right 1
        glm::vec3( 0.5f, -0.5f, -0.5f), // bottom right 2
        glm::vec3(-0.5f, -0.5f, -0.5f), // bottom left 3
    } },
    { LEFT, {
        glm::vec3(-0.5f,  0.5f, -0.5f), // top left 0
        glm::vec3(-0.5f,  0.5f,  0.5f), // top right 1
        glm::vec3(-0.5f, -0.5f,  0.5f), // bottom right 2
        glm::vec3(-0.5f, -0.5f, -0.5f), // bottom left 3
    } },
    { RIGHT, {
        glm::vec3( 0.5f,  0.5f, -0.5f), // top left 0
        glm::vec3( 0.5f,  0.5f,  0.5f), // top right 1
        glm::vec3( 0.5f, -0.5f,  0.5f), // bottom right 2
        glm::vec3( 0.5f, -0.5f, -0.5f), // bottom left 3
    } },
    { TOP, {
        glm::vec3(-0.5f,  0.5f, -0.5f), // top left 0
        glm::vec3( 0.5f,  0.5f, -0.5f), // top right 1
        glm::vec3( 0.5f,  0.5f,  0.5f), // bottom right 2
        glm::vec3(-0.5f,  0.5f,  0.5f), // bottom left 3
    } },
    { BOTTOM, {
        glm::vec3(-0.5f, -0.5f, -0.5f), // top left 0
        glm::vec3( 0.5f, -0.5f, -0.5f), // top right 1
        glm::vec3( 0.5f, -0.5f,  0.5f), // bottom right 2
        glm::vec3(-0.5f, -0.5f,  0.5f), // bottom left 3
    } },
};


inline static std::vector<float> textureData = {
    0.0f, 1.0f, // top left
    1.0f, 1.0f, // top right
    1.0f, 0.0f, // bottom right
    0.0f, 0.0f, // bottom left
};
inline static std::unordered_map<BlockType, std::vector<float>> atlasData = {
    { EMPTY, {
        0.0f, 1.0f, // top left
        1.0f, 1.0f, // top right
        1.0f, 0.0f, // bottom right
        0.0f, 0.0f, // bottom left
    } },
    { GRASS_TOP, {
        1.0f/6, 4.0f/6, // top left
        2.0f/6, 4.0f/6, // top right
        2.0f/6, 3.0f/6, // bottom right
        1.0f/6, 3.0f/6, // bottom left
    } },
    { GRASS, { // TODO: alle top und bottom textureCoords sind vertauscht
        5.0f/6, 5.0f/6, // top left
        6.0f/6, 5.0f/6, // top right
        6.0f/6, 4.0f/6, // bottom right
        5.0f/6, 4.0f/6, // bottom left
    } },
    { STONE, {
        2.0f/6, 1.0f/6, // top left
        3.0f/6, 1.0f/6, // top right
        3.0f/6, 0.0f, // bottom right
        2.0f/6, 0.0f, // bottom left
    } },
    { DIRT, {
        3.0f/6, 5.0f/6, // top left
        4.0f/6, 5.0f/6, // top right
        4.0f/6, 4.0f/6, // bottom right
        3.0f/6, 4.0f/6, // bottom left
    } },
};




class Block
{
private:
    std::unordered_map<Faces, std::vector<glm::vec3>> processedVertexData;

public:
    BlockType type;

    Block (glm::vec3 position, BlockType type = EMPTY) // blocktype defaults to empty
        : blockPosition(position), type(type)
    {
        processedVertexData = {
            { FRONT, process_VertexData(rawVertexData[FRONT]) },
            { BACK, process_VertexData(rawVertexData[BACK]) },
            { LEFT, process_VertexData(rawVertexData[LEFT]) },
            { RIGHT, process_VertexData(rawVertexData[RIGHT]) },
            { TOP, process_VertexData(rawVertexData[TOP]) },
            { BOTTOM, process_VertexData(rawVertexData[BOTTOM]) },
        };
    }

    std::vector<glm::vec3> getFace(const Faces face)
    {
        return processedVertexData[face];
    }

    std::vector<float> getTexture(const BlockType type)
    {
        return atlasData[type];
    }

    glm::vec3 blockPosition;

private:
    std::vector<glm::vec3> process_VertexData (std::vector<glm::vec3> rawVertexData)
    {
        std::vector<glm::vec3> processedVertexData;

        for (int i = 0; i < rawVertexData.size(); i++)
        {
            processedVertexData.push_back(rawVertexData[i] + blockPosition);
        }

        return processedVertexData;
    }

};




#endif