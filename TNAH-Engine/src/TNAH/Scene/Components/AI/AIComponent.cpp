#include "tnahpch.h"
#include "AIComponent.h"

namespace tnah {


    void AIComponent::OnUpdate(Timestep deltaTime, glm::vec3 &pos)
    {
        if(wander(pos, deltaTime.GetSeconds()))
            setWander(mWanderRadius, mWanderDistance, mWanderJitter);
        
        TNAH_CORE_INFO("T x {0} z{1} y{2}", mWanderTarget.x, mWanderTarget.y, mWanderTarget.z);
        /*glm::vec3 t = {2.35, pos.y, -4.63};
        moveTo(pos, t, m_Velocity, deltaTime, 1);*/
    }

}