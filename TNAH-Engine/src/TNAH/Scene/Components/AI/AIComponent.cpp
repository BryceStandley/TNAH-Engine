#include "tnahpch.h"
#include "AIComponent.h"

namespace tnah {


    void AIComponent::OnUpdate(Timestep deltaTime, glm::vec3 &pos)
    {
        currentPosition.position = {static_cast<int>(round(pos.x)), static_cast<int>(round(pos.z))};
        if(currentlyWandering)
        {
            if(!currentPath.empty())
            {
                const auto path = currentPath.front();
                if(!AStar::IsValid(path.position))
                {
                    currentPath = {};
                }
                else if(AStar::Reached(currentPosition.position, path) || moveTo(pos, glm::vec3(path.position.x, pos.y, path.position.y), m_Velocity, deltaTime.GetSeconds()))
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

        currentPosition.position = {static_cast<int>(round(pos.x)), static_cast<int>(round(pos.z))};
    }

}