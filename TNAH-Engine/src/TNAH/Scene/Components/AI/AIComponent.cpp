#include "tnahpch.h"
#include "AIComponent.h"

namespace tnah {


    void AIComponent::OnUpdate(Timestep deltaTime, TransformComponent &trans)
    {
        currentPosition.position = {static_cast<int>(round(trans.Position.x)), static_cast<int>(round(trans.Position.z))};
        if(currentlyWandering)
        {
            if(!currentPath.empty())
            {
                const auto path = currentPath.front();
                if(!AStar::IsValid(path.position))
                {
                    currentPath = {};
                }
                else if(AStar::Reached(currentPosition.position, path) || moveTo(trans.Position, glm::vec3(path.position.x, trans.Position.y, path.position.y), m_Velocity, deltaTime.GetSeconds(), trans.Rotation))
                {
                    currentPath.pop_front();
                }
            }
            else
            {
                destination = AStar::GenerateRandomPosition(currentPosition.position);
                currentPath = AStar::Algorithm(currentPosition, destination);
            }
        }

        currentPosition.position = {static_cast<int>(round(trans.Position.x)), static_cast<int>(round(trans.Position.z))};
    }

}