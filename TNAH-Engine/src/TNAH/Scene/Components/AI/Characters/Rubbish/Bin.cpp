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
        SetActionDistance(1.5);
        SetColour(glm::vec4(1, 1, 1, 1));
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
        timer-= GetDeltaTime();
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
        if(currentAffordanceLevel >= affordanceValue && affordanceValue > 0)
        {
            if(distance <= actionDistance)
            {
                switch (Character::GetDesiredAction())
                {
                case abuse:
                    if(timer < 0)
                    {
                        switch(rand() % 3)
                        {
                        case 1:
                            LogAction("(Abuse)I hate you " + tag + "!", mColour);
                            break;
                        case 2:
                            LogAction("(Abuse)You suck " + tag + "!", mColour);
                            break;
                        default:
                            LogAction("(Abuse)You're the worst " + tag + "!", mColour);
                            break;
                        }

                        ResetTimer();
                    }
                    emotions.IncreaseArousal(0.025 * GetDeltaTime());
                    break;
                case greeting:
                    if(timer < 0)
                    {
                        switch(rand() % 3)
                        {
                        case 1:
                            LogAction("(Greeting)HALLLO " + tag + "!", mColour);
                            break;
                        case 2:
                            LogAction("(Greeting)Hey good to see " + tag + "!", mColour);
                            break;
                        default:
                            LogAction("(Greeting)Wonderful day ain't it " + tag + "!", mColour);
                            break;
                        }

                        ResetTimer();
                    }
                    emotions.IncreaseArousal(0.02* GetDeltaTime());

                    emotions.IncreaseValence(0.02* GetDeltaTime());
                    break;
                case pickup:
                        check.second = true;
                        LogAction("(Pickup)Who left rubbish here!", mColour);
                        emotions.IncreaseArousal(0.3);
                        emotions.DecreaseValence(0.4);
                    break;
                case sleep:
                    if(timer < 0)
                    {
                        LogAction("(Sleep)This looks like a good spot to snooze!", mColour);
                        ResetTimer();
                    }
                    emotions.DecreaseArousal(0.05* GetDeltaTime());
                    emotions.IncreaseValence(0.01* GetDeltaTime());
                    break;
                case none:
                default:
                    break;
                }
            }
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
