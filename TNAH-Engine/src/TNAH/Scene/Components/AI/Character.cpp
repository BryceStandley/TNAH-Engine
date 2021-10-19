#include "tnahpch.h"
#include "Character.h"

#include "Characters/BinStates.h"

namespace tnah
{
    Bin::Bin()
    {

        mFsm.reset(new StateMachine<Bin>(this));
        mFsm->setGlobalState(&global_bin::getInstance());
        //mFsm->setCurrentState
    }

    glm::vec3 Bin::OnUpdate(Timestep deltaTime)
    {
        SetDeltaTime(deltaTime.GetSeconds());
        currentAffordanceLevel = BalanceRange(0, 1, currentAffordanceLevel);
        mFsm->update();

        return targetPos;
    }

    void Bin::CheckAction(float affordanceValue, float distance)
    {
        if(currentAffordanceLevel <= affordanceValue)
        {
            if(actionDistance <= distance)
            {
                //execute
            }
            //else
                //move towards
        }
    }

    float Bin::BalanceRange(float min, float max, float balanceValue)
    {
        if(balanceValue < min)
            return min;
        else if(balanceValue > max)
            return max;
    }


}
