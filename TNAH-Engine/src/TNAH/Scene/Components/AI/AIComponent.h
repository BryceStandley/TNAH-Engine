#pragma once
# define PI           3.14159265358979323846
#include "AStar.h"
#include "Character.h"
#include "TNAH/Core/Timestep.h"

namespace tnah
{
    inline double randFloat()
    {
        return ((rand()) / (RAND_MAX + 1.0));
    }

    inline double randomClamped()
    {
        return randFloat() - randFloat();
    }
    
    class AIComponent
    {
    public:
        AIComponent()
        {
            m_Velocity = glm::vec3(1, 0 , 1);
            currentlyWandering = false;
        }

        ~AIComponent()
        {
            
        }

        const glm::vec3& GetTargetPosition() const;
        void SetTargetPosition(const glm::vec3& targetPosition);
        float TargetCutoffDistance() const;
        void SetTargetCutoffDistance(float targetCutoffDistance);
        float RotationSpeed() const;
        void SetRotationSpeed(float rotationSpeed);
        float MovementSpeed() const;
        void SetMovementSpeed(float movementSpeed);
        bool MovementAllowed() const;
        void SetMovementAllowed(bool movementAllowed);
        void SetVelocity(const glm::vec3 vel) { m_Velocity = vel; }
        void StartWander() {currentlyWandering = true;}
        void StopWander() {currentlyWandering = false;}
        /**
        * @fn void OnUpdate(Timestep deltaTime) 
        * 
        * @brief The update function for the AI component
        *
        * @author Bryce Standley
        * @date Thursday, 30 September 2021
        * 
        *
        *
        */
        void OnUpdate(Timestep deltaTime, glm::vec3 &pos);
    private:
        bool moveTo(glm::vec3& curPos, const glm::vec3& targetPos, glm::vec3& curVelocity, float time, float offset)
        {
            //calc heading from character position to target
            glm::vec3 target = targetPos - curPos;
            target = glm::normalize(target);

            if (target.x == 0 && target.y == 0 && target.z == 0)
                return true;

            //calc new velocity and new character position
            curVelocity = target * glm::length(curVelocity);
            glm::vec3 displacement = curVelocity * time;
            glm::vec3 vec = curPos + displacement;

            SetVelocity(curVelocity);

            // calculate real target position
            glm::vec3 realTargetPos = targetPos - target * offset;

            // calculate the direction from vec to realTargetPos
            glm::vec3 toRealTarget = realTargetPos - vec;
            toRealTarget = glm::normalize(toRealTarget);

            if (toRealTarget.x == 0 && toRealTarget.y == 0 && toRealTarget.z == 0)
            {
                if (realTargetPos.y < 25.0f)
                {
                    curPos = realTargetPos;
                }
                curPos = realTargetPos;
                //SetPos(curPos);
                m_TargetPosition = curPos;
                return true;
            }

            //check to see whether vec has gone pass the realTargetPos
            float dp = glm::dot(toRealTarget, target);
            TNAH_CORE_INFO("Distance {0}", dp);
            if (dp < 0.0)
            {
                if (realTargetPos.y < 25.0f)
                {
                    curPos = realTargetPos;
                }

                //SetPos(curPos);
                m_TargetPosition = curPos;
                return true;
            }
            //std::cout << curPos.x << " " << curPos.y << " " << curPos.z << " | " << vec.x << " " << vec.y << " " << vec.z << std::endl;
            curPos = vec;

            //SetPos(curPos);
            m_TargetPosition = curPos;
            return false;
        }

    private:
        glm::vec3 m_TargetPosition = {};
        float m_TargetCutoffDistance = 1.0f;
        float m_MovementSpeed = 1.0f;
        bool m_MovementAllowed = true;
        glm::vec3 m_Velocity = {};
        bool currentlyWandering = false;
        //AStar stuff
        Node currentPosition;
        std::vector<Node> currentPath = {};
    };

    inline const glm::vec3& AIComponent::GetTargetPosition() const
    {
        return m_TargetPosition;
    }

    inline void AIComponent::SetTargetPosition(const glm::vec3& targetPosition)
    {
        m_TargetPosition = targetPosition;
    }

    inline float AIComponent::TargetCutoffDistance() const
    {
        return m_TargetCutoffDistance;
    }

    inline void AIComponent::SetTargetCutoffDistance(float targetCutoffDistance)
    {
        m_TargetCutoffDistance = targetCutoffDistance;
    }

    inline float AIComponent::MovementSpeed() const
    {
        return m_MovementSpeed;
    }

    inline void AIComponent::SetMovementSpeed(float movementSpeed)
    {
        m_MovementSpeed = movementSpeed;
    }

    inline bool AIComponent::MovementAllowed() const
    {
        return m_MovementAllowed;
    }

    inline void AIComponent::SetMovementAllowed(bool movementAllowed)
    {
        m_MovementAllowed = movementAllowed;
    }
}
