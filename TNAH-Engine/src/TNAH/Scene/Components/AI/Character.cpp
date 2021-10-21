#include "tnahpch.h"
#include "Character.h"

#include "Characters/BinStates.h"
#include "TNAH/Core/Application.h"

namespace tnah
{
    //Bin
    Bin::Bin()
    {

        mFsm.reset(new StateMachine<Bin>(this));
        mFsm->setGlobalState(&global_bin::getInstance());
        SetDesiredAction(sit);
        SetDistance(10);
        actionDistance = 1.5;
        mColour = glm::vec4(1, 1, 0, 1);
        currentAffordanceLevel = 1.0f;
        //Temporary stuff
        emotions.AddTrait(Trait::Happy);
        emotions.AddTrait(Trait::Carefree);
        emotions.SetMood(Mood::Happy);
        mCharacterState = emotions.GetEmotion();
        Character::name = "bin";
        //mFsm->setCurrentState
    }

    glm::vec3 Bin::OnUpdate(Timestep deltaTime)
    {
        SetDeltaTime(deltaTime.GetSeconds());
        currentAffordanceLevel = BalanceRange(0, 1, currentAffordanceLevel);
        emotions.Update();
        mFsm->update();

        return targetPos;
    }

    void Bin::CheckAction(float affordanceValue, float distance)
    {
        if(currentAffordanceLevel <= affordanceValue)
        {
            if(distance <= actionDistance)
            {
                switch (Character::GetDesiredAction())
                {
                case kick:
                    if(canOutput)
                    {
                        LogAction("Kicked something" + std::to_string(distance), mColour);
                        canOutput = false;
                    }
                    emotions.IncreaseArousal(0.1 * GetDeltaTime());
                    break;
                case punch:
                case sit:
                    if(canOutput)
                    {
                        LogAction("Sat on something", mColour);
                        canOutput = false;
                    }
                    emotions.DecreaseArousal(0.1 * GetDeltaTime());
                    emotions.IncreaseValence(0.1 * GetDeltaTime());
                    break;
                case none:
                default:
                    break;
                }
            }
            else
                canOutput = true;
        }
    }

    float Bin::BalanceRange(float min, float max, float balanceValue)
    {
        if(balanceValue < min)
            return min;
        else if(balanceValue > max)
            return max;
    }

    void Character::LogAction(std::string text, glm::vec4 colour)
    {
        Application::LogPush(LogText(name + ": " + text, colour));
    }

    PlayerCharacter::PlayerCharacter()
    {
        mFsm.reset(new StateMachine<PlayerCharacter>(this));
        SetDesiredAction(sit);
        SetDistance(10);
        actionDistance = 1.5;
        mColour = glm::vec4(1, 1, 0, 1);
        currentAffordanceLevel = 1.0f;
        //Temporary stuff
        Character::name = "player";
        //mFsm->setCurrentState
    }

    glm::vec3 PlayerCharacter::OnUpdate(Timestep deltaTime)
    {
        SetDeltaTime(deltaTime.GetSeconds());
        currentAffordanceLevel = BalanceRange(0, 1, currentAffordanceLevel);
        mFsm->update();

        return targetPos;
    }

    void PlayerCharacter::CheckAction(float affordanceValue, float distance)
    {
        if(currentAffordanceLevel <= affordanceValue)
        {
            if(distance <= actionDistance)
            {
                switch (Character::GetDesiredAction())
                {
                default:
                    break;
                }
            }
            else
                canOutput = true;
        }
    }

    float PlayerCharacter::BalanceRange(float min, float max, float balanceValue)
    {
        if(balanceValue < min)
            return min;
        else if(balanceValue > max)
            return max;
    }


}
