#include "tnahpch.h"
#include "Bin.h"

#include "BinStates.h"

namespace tnah
{
    Bin::Bin()
    {

        mFsm.reset(new StateMachine<Bin>(this));
        mFsm->setGlobalState(&GlobalStateBin::getInstance());
        SetDesiredAction(sit);
        SetDistance(10);
        actionDistance = 1.5;
        mColour = glm::vec4(1, 1, 1, 1);
        currentAffordanceLevel = 1.0f;
        
        emotions.SetArousal(0.33f);
        emotions.SetValence(0.5f);
        
        emotions.AddTrait(Trait::Happy);
        emotions.AddTrait(Trait::Carefree);

        emotions.SetMood(Mood::Happy);
  
        Character::name = "Bin";
    }

    glm::vec3 Bin::OnUpdate(Timestep deltaTime, TransformComponent &transform)
    {
        SetDeltaTime(deltaTime.GetSeconds());
        currentAffordanceLevel = BalanceRange(0, 1, currentAffordanceLevel);
        emotions.Update(deltaTime.GetSeconds());
        mFsm->update();

        if(spin)
        {
            transform.Rotation.y += 10 * GetDeltaTime();
        }

        return targetPos;
    }

    std::pair<bool, bool> Bin::CheckAction(float affordanceValue, float distance, std::string tag)
    {
        std::pair<bool, bool> check;
        check.second = false;
        check.first = false;
        if(currentAffordanceLevel >= affordanceValue)
        {
            if(distance <= actionDistance)
            {
                switch (Character::GetDesiredAction())
                {
                case abuse:
                    if(canOutput)
                    {
                        switch(rand() % 3)
                        {
                        case 1:
                            LogAction("I hate you add name here!", mColour);
                            break;
                        case 2:
                            LogAction("You suck add name here!", mColour);
                            break;
                        default:
                            LogAction("You're the worst add name here!", mColour);
                            break;
                        }
                        canOutput = false;

                        emotions.IncreaseArousal(0.25);
                        previousState = GetDesiredAction();
                    }
                    break;
                case greeting:
                    if(canOutput)
                    {
                        switch(rand() % 3)
                        {
                        case 1:
                            LogAction("Your such a good person name here!", mColour);
                            break;
                        case 2:
                            LogAction("Hey good to see you name here!", mColour);
                            break;
                        default:
                            LogAction("Wonderful day ain't it add name here!", mColour);
                            break;
                        }
                        canOutput = false;

                        emotions.IncreaseArousal(0.2);
                        emotions.IncreaseValence(0.2);
                        previousState = GetDesiredAction();
                    }
                    break;
                case pickup:
                        check.second = true;
                        LogAction("Who left rubbish here!", mColour);
                        emotions.IncreaseArousal(0.3);
                        emotions.DecreaseValence(0.4);
                        previousState = GetDesiredAction();
                    break;
                case sleep:
                    if(canOutput)
                    {
                        LogAction("This looks like a good spot to snooze!", mColour);
                        canOutput = false;
                        emotions.DecreaseArousal(0.5);
                        emotions.IncreaseValence(0.5);
                        previousState = GetDesiredAction();
                    }
                    break;
                case none:
                default:
                    break;
                }
            }
            else if(previousState != GetDesiredAction())
                canOutput = true;
        }

        return check;
    }

    float Bin::BalanceRange(float min, float max, float balanceValue)
    {
        if(balanceValue < min)
            return min;
        else if(balanceValue > max)
            return max;
    }

    void Bin::ApplyPlayerAction(PlayerActions givenAction)
    {
        switch (givenAction)
        {
        case PlayerActions::insult:
            emotions.DecreaseValence(0.5 * GetDeltaTime());
            break;
        case PlayerActions::compliment:
            emotions.IncreaseValence(0.5 * GetDeltaTime());
            break;
        case PlayerActions::calm:
            emotions.DecreaseArousal(0.5 * GetDeltaTime());
            break;
        case PlayerActions::pumpUp:
            emotions.IncreaseArousal(0.5 * GetDeltaTime());
            break;
        default:
            break;
        }
    }

    std::string Bin::CharacterString()
    {
        std::string str;
        str += "Name: Bin\nEmotion: " + emotions.GetCurrentEmotionAsString() + "\nMood: " + emotions.GetCurrentMoodAsString() +
            "\n" + emotions.GetTraitsAsString() +
            "\nArousal: " + std::to_string(emotions.GetArousal()) + "\nPositiveArousalMultiplier" + std::to_string(emotions.GetPositiveArosualMultiplier()) +
            "\nNegativeArousalMultiplier" + std::to_string(emotions.GetNegativeArousalMultiplier()) + "\nValence: " + std::to_string(emotions.GetValence()) +
            "\nPositiveValenceMultiplier" + std::to_string(emotions.GetPositiveArosualMultiplier()) + "\nNegativeValenceMultiplier"
            + std::to_string(emotions.GetNegativeValenceMultiplier()) + "\nAction: " + GetActionString(GetDesiredAction());
        return str;
    }

}
