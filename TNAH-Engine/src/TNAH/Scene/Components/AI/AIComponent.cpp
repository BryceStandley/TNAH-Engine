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
                auto path = currentPath.back();

                if(AStar::Reached(currentPosition.position, path))
                {
                    currentPath.pop_back();
                }
                else
                    moveTo(pos, glm::vec3(path.position.x, pos.y, path.position.y), m_Velocity, deltaTime.GetSeconds());
            }
            else
            {
                currentPath = AStar::Algorithm(currentPosition, AStar::GenerateRandomPosition(currentPosition.position));
            }
        }

        currentPosition.position = {static_cast<int>(round(pos.x)), static_cast<int>(round(pos.z))};
    }

}