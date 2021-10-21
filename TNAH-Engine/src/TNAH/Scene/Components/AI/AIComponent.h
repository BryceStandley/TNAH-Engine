#pragma once
# define PI           3.14159265358979323846
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
            setWander(10.0, 1.0, 10.0);
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
        void SetWanderRadius(float r) { mWanderRadius = r;}
        void SetWanderJitter(float r) { mWanderJitter = r;}
        void SetWanderDistance(float r) { mWanderDistance = r;}
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

        void pursue(const glm::vec3& evaderPos, glm::vec3& pursuerPos, const glm::vec3& evaderVelocity,
                    glm::vec3& pursuerVelocity, float time, float offset, std::string type)
        {
            double lookAheadTime;

            //distance between evader and pursuer
            glm::vec3 toEvader = evaderPos - pursuerPos;

            //compute two agents headings
            glm::vec3 pursuerHeading = pursuerVelocity;
            pursuerHeading = glm::normalize(pursuerHeading);

            glm::vec3 evaderHeading = evaderVelocity;
            evaderHeading = glm::normalize(evaderHeading);

            //compute angle between two agents 
            double relativeHeading = glm::dot(pursuerHeading, evaderHeading);

            //std::cout << "relativeHeading = " << relativeHeading << std::endl;

            //std::cout << "Evader Velocity Length:  " << glm::length(evaderVelocity) << std::endl;

            //determine if evader is facing pursuer
            if ((relativeHeading < -0.95) || glm::length(evaderVelocity) == 1)
            {
                //moveTo(pursuerPos, evaderPos, pursuerVelocity, time, offset, type);
                m_TargetPosition = pursuerPos;
                //std::cout << "In eyesight" << std::endl;
            }
            else
            {
                lookAheadTime = (glm::length(toEvader)) / (glm::length(evaderVelocity) + glm::length(pursuerVelocity));
                //moveTo(pursuerPos, evaderPos + evaderVelocity * (float)lookAheadTime, pursuerVelocity, time, offset, type);
                m_TargetPosition = pursuerPos;
                //std::cout << "outta eyesight" << std::endl;
            }
        }

        bool flee(glm::vec3& curPos, const glm::vec3& pursuerPos, glm::vec3& curVelocity, float fleeSpeed, float time,
                  std::string type)
        {
            glm::vec3 fromPursuer = curPos - pursuerPos;

            float panic = 100.0f * 100.0f;

            if (fromPursuer.length() > panic)
                return false;

            fromPursuer = glm::normalize(fromPursuer);
            curVelocity = fromPursuer * fleeSpeed;
            //SetPos(curPos + curVelocity * time);
            m_TargetPosition = curPos;
            return true;
        }

        bool evade(glm::vec3& evaderPos, const glm::vec3& pursuerPos, glm::vec3& evaderVelocity,
                   const glm::vec3& pursuerVelocity, float time, std::string type)
        {
            //distance between pursuer and evader
            glm::vec3 toPursuer = pursuerPos - evaderPos;

            float lookAheadTime = toPursuer.length() / (evaderVelocity.length() + pursuerVelocity.length());

            return (flee(evaderPos, pursuerPos + pursuerVelocity * lookAheadTime, evaderVelocity,
                         evaderVelocity.length(), time, type));
        }

        void setWander(double wanderRadius, double wanderDistance, double wanderJitter)
        {
            wanderRadius = wanderRadius;
            wanderDistance = wanderDistance;
            wanderJitter = wanderJitter;
            double theta = ((rand()) / (RAND_MAX + 1.0)) * (2 * PI);
            mWanderTarget = {cos(theta), 0, sin(theta)};
        }

        bool wander(glm::vec3& position, float deltaTime)
        {
            float jitter = mWanderJitter * deltaTime;
            mWanderTarget += glm::vec3(randomClamped() * jitter, 0.0, randomClamped() * jitter);
            //reproject the new vector back on to a unit circle
            mWanderTarget = glm::normalize(mWanderTarget);
            //TNAH_CORE_INFO("WT x {0} z{1} y{2}", mWanderTarget.x, mWanderTarget.y, mWanderTarget.z);
            glm::vec3 heading(m_Velocity);
            heading = glm::normalize(heading);
            //TNAH_CORE_INFO("H x {0} z{1} y{2}", heading .x, heading .y, heading .z);
            glm::vec3 wanderCircleWorldCentre = position + (heading * mWanderDistance);
            //TNAH_CORE_INFO("WC x {0} z{1} y{2}", wanderCircleWorldCentre .x, wanderCircleWorldCentre .y, wanderCircleWorldCentre .z);
            //project the wanderTarget to the enlarged wander circle in the world
            glm::vec3 targetWorld = wanderCircleWorldCentre + (mWanderTarget * mWanderRadius);
            //TNAH_CORE_INFO("MT x {0} z{1} y{2}", mWanderTarget.x, mWanderTarget.y, mWanderTarget.z);
            //TNAH_CORE_INFO("TW x {0} z{1} y{2}", targetWorld.x, targetWorld.y, targetWorld.z);
            //move to the new target position
            return moveTo(position, targetWorld, m_Velocity, deltaTime, 1);
        }

    private:
        glm::vec3 m_TargetPosition = {};
        float m_TargetCutoffDistance = 1.0f;
        float m_RotationSpeed = 1.0f;
        float m_MovementSpeed = 1.0f;
        bool m_MovementAllowed = true;
        glm::vec3 m_Velocity = {};
        float mWanderRadius = 5.0f;
        float mWanderDistance = 1.0f;
        float mWanderJitter = 1.0f;
        glm::vec3 mWanderTarget = {};
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

    inline float AIComponent::RotationSpeed() const
    {
        return m_RotationSpeed;
    }

    inline void AIComponent::SetRotationSpeed(float rotationSpeed)
    {
        m_RotationSpeed = rotationSpeed;
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
