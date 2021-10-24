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
                TNAH_CORE_INFO("Path point {0} {1} Size{2}", path.position.x, path.position.y, currentPath.size());
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

        TNAH_CORE_INFO("Dest {0} {1}", destination.position.x, destination.position.y);

        currentPosition.position = {static_cast<int>(round(pos.x)), static_cast<int>(round(pos.z))};
    }

}