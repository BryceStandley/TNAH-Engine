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

        Character::name = "Student";
 
    }

    glm::vec3 Student::OnUpdate(Timestep deltaTime, TransformComponent& transform)
    {
        SetDeltaTime(deltaTime.GetSeconds());
        currentAffordanceLevel = BalanceRange(0, 1, currentAffordanceLevel);
        emotions.Update();
        mFsm->update();

        return targetPos;
    }

    std::pair<bool, bool> Student::CheckAction(float affordanceValue, float distance, std::string tag)
    {
        std::pair<bool, bool> check;
        check.second = false;
        check.first = false;
        if (currentAffordanceLevel <= affordanceValue)
        {
            if (distance <= actionDistance)
            {
                switch (Character::GetDesiredAction())
                {
                    case sit:
                        if (canOutput)
                        {
                            LogAction("(Sits) This looks like a nice spot to sit!", mColour);
                            canOutput = false;
                            SetWander(false);
                        }
                        emotions.DecreaseArousal(0.05 * GetDeltaTime());
                        emotions.IncreaseValence(0.1 * GetDeltaTime());
                        previousState = GetDesiredAction();
                        break;
                case greeting:
                    if (canOutput)
                    {
                        switch (rand() % 3)
                        {
                        case 1:
                            LogAction("(Greet) Aye " + tag, mColour);
                            break;
                        case 2:
                            LogAction("(Greet) Sup " + tag, mColour);
                            break;
                        default:
                            LogAction("(Greet) Legend " + tag, mColour);
                            break;
                        }
                        canOutput = false;

                        emotions.IncreaseArousal(0.2);
                        emotions.IncreaseValence(0.2);
                        previousState = GetDesiredAction();
                    }
                    break;
                case sleep:
                    if (canOutput)
                    {
                        LogAction("(Sleeps) This looks like a good spot to snooze!", mColour);
                        canOutput = false;
                        SetWander(false);
                    }
                    emotions.DecreaseArousal(0.1 * GetDeltaTime());
                    emotions.IncreaseValence(0.2 * GetDeltaTime());
                    previousState = GetDesiredAction();
                    break;
                case play:
                    if (canOutput)
                    {
                        LogAction("(Plays" + tag + " here) This looks fun to play!", mColour);
                        canOutput = false;
                        SetWander(false);
                    }
                    emotions.IncreaseArousal(0.1 * GetDeltaTime());
                    emotions.IncreaseValence(0.1 * GetDeltaTime());
                    previousState = GetDesiredAction();
                    break;
                case drink:
                    check.second = true;
                    LogAction("(Drinks " + tag + ") Yum! Delicious drink!", mColour);
                    emotions.IncreaseArousal(0.25);
                    break;
                    case kick:
                        if (canOutput)
                        {
                            LogAction("(Kicks "+ tag + ")", mColour);
                            canOutput = false;
                            SetWander(false);
                            emotions.IncreaseArousal(0.2);
                            emotions.DecreaseValence(0.2);
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

    std::string Student::CharacterString()
    {
        std::string str;
        str += "Name: Student\nEmotion: " + emotions.GetCurrentEmotionAsString() + "\nMood: " + emotions.GetCurrentMoodAsString() +
            "\n" + emotions.GetTraitsAsString() +
            "\nArousal: " + std::to_string(emotions.GetArousal()) + "\nPositiveArousalMultiplier" + std::to_string(emotions.GetPositiveArosualMultiplier()) +
            "\nNegativeArousalMultiplier" + std::to_string(emotions.GetNegativeArousalMultiplier()) + "\nValence: " + std::to_string(emotions.GetValence()) +
            "\nPositiveValenceMultiplier" + std::to_string(emotions.GetPositiveArosualMultiplier()) + "\nNegativeValenceMultiplier"
            + std::to_string(emotions.GetNegativeValenceMultiplier()) + "\nAction: " + GetActionString(GetDesiredAction());
        return str;
    }
}