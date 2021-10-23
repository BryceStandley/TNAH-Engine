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

        for(Node n : currentPath)
        {
            TNAH_CORE_INFO("Posiitons {0} {1}", n.position.x, n.position.y);
        }

        currentPosition.position = {static_cast<int>(round(pos.x)), static_cast<int>(round(pos.z))};
        //if(wander(pos, deltaTime.GetSeconds()))
            //setWander(mWanderRadius, mWanderDistance, mWanderJitter);
        
        //TNAH_CORE_INFO("T x {0} z{1} y{2}", mWanderTarget.x, mWanderTarget.y, mWanderTarget.z);
        /*glm::vec3 t = {2.35, pos.y, -4.63};
        moveTo(pos, t, m_Velocity, deltaTime, 1);*/
    }

}