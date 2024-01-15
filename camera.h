#ifndef CAMERA_H
#define CAMERA_H

#include "includes/glad.h"
#include "includes/glm/glm.hpp"
#include "includes/glm/gtc/matrix_transform.hpp"

#include <vector>

enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    UP,
    DOWN,
    SPRINT
};

// default values
const float YAW = 0.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a action vector pointing to the right so we initially rotate a bit to the left.
const float PITCH =  0.0f;
const float SPEED =  5.0f;
const float SENSITIVITY = 0.05f;
const float ZOOM  =  70.0f;

class Camera {
public:

    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;

    float Yaw;
    float Pitch;

    float MovementSpeed;
    float MouseSensitivity;
    float Zoom;

    // constructor vectors
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH)
        : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
    {
        Position = position;
        WorldUp = up;
        Yaw = yaw;
        Pitch = pitch;
        updateCameraVectors();
    }

    // constructor scalars
    Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch)
        : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
    {
        Position = glm::vec3(posX, posY, posZ);
        WorldUp = glm::vec3(upX, upY, upZ);
        Yaw = yaw;
        Pitch = pitch;
        updateCameraVectors();
    }

    // return view matrix
    glm::mat4 GetViewMatrix() {
        return glm::lookAt(Position, Position + Front, Up);
    }


    void ProcessKeyboard(Camera_Movement action, float deltaTime) {
        float velocity = MovementSpeed * deltaTime;

        if (action == FORWARD)
            Position += Front * velocity;
        if (action == BACKWARD)
            Position -= Front * velocity;
        if (action == LEFT)
            Position -= Right * velocity;
        if (action == RIGHT)
            Position += Right * velocity;
        if (action == UP)
            Position += Up * velocity;
        if (action == DOWN)
            Position -= Up * velocity;
        
        if (action == SPRINT)
            MovementSpeed = SPEED * 3;
        else
            MovementSpeed = SPEED;
    }

    void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true) {
        xoffset *= MouseSensitivity;
        yoffset *= MouseSensitivity;

        Yaw += xoffset;
        Pitch += yoffset;

        // make sure that when pitch is out of bounds, screen doesn't get flipped
        if (constrainPitch) {
            if (Pitch > 89.0f)
                Pitch = 89.0f;
            if (Pitch < -89.0f)
                Pitch = -89.0f;
        }

        // update Front, Right and Up Vectors using the updated Euler angles
        updateCameraVectors();
    }

    void ProcessMouseScroll(float yoffset) {
        Zoom -= (float)yoffset*2;

        std::cout << "Zoom: " << Zoom << std::endl;

        // prevent zooming in or out too much
        if (Zoom < 1.0f)
            Zoom = 1.0f;
        if (Zoom > 70.0f)
            Zoom = 70.0f;
    }

private:

    // calculates the front vector from the Camera's (updated) Euler Angles
    void updateCameraVectors() {
        // calculate the new Front vector
        glm::vec3 front;
        front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        front.y = sin(glm::radians(Pitch));
        front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        Front = glm::normalize(front);
        // also re-calculate the Right and Up vector
        Right = glm::normalize(glm::cross(Front, WorldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
        Up    = glm::normalize(glm::cross(Right, Front));

        // print camera position
        std::cout << "Camera Position: " << Position.x << " " << Position.y << " " << Position.z << std::endl;
    }

};

#endif // CAMERA_H