#include "tnahpch.h"
#include "Student.h"
#include "StudentStates.h"

namespace tnah
{
    //Student
    Student::Student()
    {

        mFsm.reset(new StateMachine<Student>(this));
        mFsm->setGlobalState(&GlobalStateStudent::getInstance());
        SetDesiredAction(sit);
        SetDistance(10);
        actionDistance = 1.5;
        mColour = glm::vec4(0, 1, 0, 0);
        currentAffordanceLevel = 1.0f;
        
        emotions.SetArousal(-0.33f);
        emotions.SetValence(0.5f);
        
        emotions.AddTrait(Trait::Happy);
        emotions.AddTrait(Trait::Carefree);
        emotions.AddTrait(Trait::Impatient);
        
        emotions.SetMood(Mood::Happy);

        mCharacterState = emotions.GetEmotion();
        Character::name = "Student";
        //mFsm->setCurrentState
    }

    glm::vec3 Student::OnUpdate(Timestep deltaTime, TransformComponent& transform)
    {
        SetDeltaTime(deltaTime.GetSeconds());
        currentAffordanceLevel = BalanceRange(0, 1, currentAffordanceLevel);
        emotions.Update();
        mFsm->update();

        //if (spin)
        {
            transform.Rotation.y += 10 * GetDeltaTime();
        }

        return targetPos;
    }

    bool Student::CheckAction(float affordanceValue, float distance, std::string tag)
    {
        bool r = false;
        if (currentAffordanceLevel <= affordanceValue)
        {
            if (distance <= actionDistance)
            {
                switch (Character::GetDesiredAction())
                {
                    case sit:
                        break;
                case greeting:
                    if (canOutput)
                    {
                        switch (rand() % 3)
                        {
                        case 1:
                            LogAction("Ayee name here!", mColour);
                            break;
                        case 2:
                            LogAction("Sup name here!", mColour);
                            break;
                        default:
                            LogAction("Legend add name here!", mColour);
                            break;
                        }
                        canOutput = false;

                        emotions.IncreaseArousal(0.2);
                        emotions.IncreaseValence(0.2);
                    }
                    break;
                case sleep:
                    if (canOutput)
                    {
                        LogAction("This looks like a good spot to snooze!", mColour);
                        canOutput = false;
                    }
                    emotions.DecreaseArousal(0.1 * GetDeltaTime());
                    emotions.IncreaseValence(0.2 * GetDeltaTime());
                    break;
                case play:
                    
                    break;
                case drink:
                    
                    break;
                    case kick:
                        break;
                case none:
                default:
                    break;
                }
            }
            else
                canOutput = true;
        }

        return r;
    }

    float Student::BalanceRange(float min, float max, float balanceValue)
    {
        if (balanceValue < min)
            return min;
        else if (balanceValue > max)
            return max;
    }

    void Student::ApplyPlayerAction(PlayerActions givenAction)
    {
        switch (givenAction)
        {
        case PlayerActions::insult:
            emotions.DecreaseValence(0.5 * GetDeltaTime());
            break;
        case PlayerActions::compliment:
            emotions.IncreaseValence(0.2 * GetDeltaTime());
            break;
        case PlayerActions::calm:
            emotions.DecreaseArousal(0.2 * GetDeltaTime());
            break;
        case PlayerActions::pumpUp:
            emotions.IncreaseArousal(0.2 * GetDeltaTime());
            break;
        default:
            break;
        }
    }
}