#pragma once

#include "Character.h"
#include "TNAH/Core/Timestep.h"
namespace tnah {

    class AIComponent
    {
    public:
        AIComponent()
        {

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
        void OnUpdate(Timestep deltaTime);
    private:
    
    private:
        glm::vec3 m_TargetPosition = {};
        float m_TargetCutoffDistance = 1.0f;
        float m_RotationSpeed = 1.0f;
        float m_MovementSpeed = 1.0f;
        bool m_MovementAllowed = true;
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
