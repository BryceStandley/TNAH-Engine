#include "Student.h"
#include "StudentStates.h"

    //Student
    Student::Student()
    {

        mFsm.reset(new StateMachine<Student>(this));
        mFsm->setGlobalState(&GlobalStateStudent::getInstance());
        SetDesiredAction(sit);
        SetDistance(10);
        SetActionDistance(1.5);
        SetColour(glm::vec4(1, 1, 1, 1));
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
        emotions.Update(deltaTime.GetSeconds());
        timer -= GetDeltaTime();
        mFsm->update();

        return targetPos;
    }

    std::pair<bool, bool> Student::CheckAction(float affordanceValue, float distance, std::string tag)
    {
        std::pair<bool, bool> check;
        check.second = false;
        check.first = false;
        if (affordanceValue >= currentAffordanceLevel && affordanceValue > 0)
        {
            if (distance <= actionDistance)
            {
                switch (Character::GetDesiredAction())
                {
                    case sit:
                        if (timer < 0)
                        {
                            LogAction("(Sits) This looks like a nice spot to sit!", mColour);
                            SetWander(false);
                            ResetTimer();
                        }
                        emotions.DecreaseArousal(0.05f * GetDeltaTime());
                        emotions.IncreaseValence(0.1f * GetDeltaTime());
                        previousState = GetDesiredAction();
                        break;
                case greeting:
                    if (timer < 0)
                    {
                        ResetTimer();
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


                    }                        emotions.IncreaseArousal(0.02f * GetDeltaTime());
                                             emotions.IncreaseValence(0.02f * GetDeltaTime());
                    break;
                case sleep:
                    if (timer < 0)
                    {
                        LogAction("(Sleeps) This looks like a good spot to snooze!", mColour);
                        SetWander(false);
                        ResetTimer();
                    }                        emotions.DecreaseArousal(0.05f * GetDeltaTime());
                                             emotions.IncreaseValence(0.05f * GetDeltaTime());
                    break;
                case play:
                    if (timer < 0)
                    {
                        LogAction("(Plays" + tag + " here) This looks fun to play!", mColour);
                        SetWander(false);
                        ResetTimer();
                    }
                    emotions.IncreaseArousal(0.02f * GetDeltaTime());
                    emotions.IncreaseValence(0.02f * GetDeltaTime());
                    break;
                case drink:
                    check.second = true;
                    LogAction("(Drinks " + tag + ") Yum! Delicious drink!", mColour);
                    emotions.IncreaseArousal(0.25);
                    previousState = GetDesiredAction();
                    break;
                    case kick:
                        if (timer < 0)
                        {
                            LogAction("(Kicks "+ tag + ")", mColour);
                            SetWander(false);
                            ResetTimer();
                        }
                    emotions.IncreaseArousal(0.02f * GetDeltaTime());
                    emotions.DecreaseValence(0.02f * GetDeltaTime());
                        break;
                case none:
                default:
                    break;
                }
            }
        }

        return check;
    }



    void Student::ApplyPlayerAction(PlayerActions givenAction)
    {
        switch (givenAction)
        {
        case PlayerActions::insult:
            emotions.DecreaseValence(0.5f * GetDeltaTime());
            break;
        case PlayerActions::compliment:
            emotions.IncreaseValence(0.5f * GetDeltaTime());
            break;
        case PlayerActions::calm:
            emotions.DecreaseArousal(0.5f * GetDeltaTime());
            break;
        case PlayerActions::pumpUp:
            emotions.IncreaseArousal(0.5f * GetDeltaTime());
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