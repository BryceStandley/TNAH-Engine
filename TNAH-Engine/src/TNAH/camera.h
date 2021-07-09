#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Terrain.h"
#include <vector>

    /**
     * @brief Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods
     */

enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

    /// Default camera values
const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;

    /**
    * @class Camera
    * @brief A camera class that processes input and calculates the corresponding Euler Angles, Vectors and Matrices for use in OpenGL
    *
    * @author Dylan Blereau
    * @version 01
    * @date 24/03/2021 Dylan Blereau, Started
    *
    **/
class Camera
{
public:
        /// camera Attributes
    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;
        /// euler Angles
    float Yaw;
    float Pitch;
        /// camera options
    float MovementSpeed;
    float MouseSensitivity;
    float Zoom;

    bool disabled = false;


        /**
        * @brief a constructor that allows you to set various variables for the camera
        * @param position - camera position 
        * @param up - up axis
        * @param yaw - yaw value 
        * @param pitch - pitch value
        */
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
    {
        Position = position;
        WorldUp = up;
        Yaw = yaw;
        Pitch = pitch;
        updateCameraVectors();

    }


        /**
        * @param posX - position on the x-axis
        * @param posY - position on the y-axis
        * @param posZ - position on the z-axis
        * @param upX - up position on the x-axis
        * @param upY - up position on the y-axis
        * @param upZ - up position on the z-axis
        * @param yaw - yaw value
        * @param pitch - ptich value
        */
    Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
    {
        Position = glm::vec3(posX, posY, posZ);
        WorldUp = glm::vec3(upX, upY, upZ);
        Yaw = yaw;
        Pitch = pitch;
        updateCameraVectors();
    }


        /**
        * @brief gets and returns the view matrix 
        * @return glm::mat4 
        */
    glm::mat4 GetViewMatrix()
    {
        return glm::lookAt(Position, Position + Front, Up);
    }


        /**
        * @brief processes input from keyboard and will performs actions dependant on the key pressed
        * @param direction - represents the movement directions
        * @param deltaTime - represents deltatime (the time between the current frame and the last frame)
        */
    void ProcessKeyboard(Camera_Movement direction, float deltaTime)
    {
        if(disabled) return;
        float velocity = MovementSpeed * deltaTime;
        if (direction == FORWARD)
            Position += Front * velocity;
        if (direction == BACKWARD)
            Position -= Front * velocity;
        if (direction == LEFT)
            Position -= Right * velocity;
        if (direction == RIGHT)
            Position += Right * velocity;
    }


        /**
        * @brief - processes input from mouse input
        * @param xoffset - offset in the x direction
        * @param yoffset - offset in the y direction
        * @param constrainPitch - flag that ensures pitch is constrained to screen doesn't flip
        */
    void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true)
    {
        if(disabled) return;
        xoffset *= MouseSensitivity;
        yoffset *= MouseSensitivity;

        Yaw += xoffset;
        Pitch += yoffset;

            /// make sure that when pitch is out of bounds, screen doesn't get flipped
        if (constrainPitch)
        {
            if (Pitch > 89.0f)
                Pitch = 89.0f;
            if (Pitch < -89.0f)
                Pitch = -89.0f;
        }

            /// update Front, Right and Up Vectors using the updated Euler angles
        updateCameraVectors();
    }

        /**
        * @brief processes input when scrolling mouse wheel. Will zoom in and out accordingly
        * @param yoffset - offset in the y direction
        */
    void ProcessMouseScroll(float yoffset)
    {
        if(disabled) return;
        Zoom -= (float)yoffset;
        if (Zoom < 1.0f)
            Zoom = 1.0f;
        if (Zoom > 45.0f)
            Zoom = 45.0f;
    }

private:

        /**
        * @brief calculates and updates vectors 
        */
    void updateCameraVectors()
    {
            /// calculate the new Front vector
        glm::vec3 front;
        front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        front.y = sin(glm::radians(Pitch));
        front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        Front = glm::normalize(front);
            /// also re-calculate the Right and Up vector
            /// normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
        Right = glm::normalize(glm::cross(Front, WorldUp));  
        Up = glm::normalize(glm::cross(Right, Front));
    }
};
#endif