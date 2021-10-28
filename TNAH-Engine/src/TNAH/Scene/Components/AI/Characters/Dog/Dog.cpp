#include "tnahpch.h"
#include "Dog.h"
#include "DogStates.h"
#include "TNAH/Audio/Audio.h"

namespace tnah
{
    // Taco the Dog - he's cute but he ain't nice mate
    Dog::Dog()
    {

        mFsm.reset(new StateMachine<Dog>(this));
        mFsm->setGlobalState(&GlobalStateDog::getInstance());
        SetDesiredAction(sit);
        SetDistance(10);
        actionDistance = 1.5;
        mColour = glm::vec4(1, 1, 1, 1);
        currentAffordanceLevel = 1.0f;
        
        emotions.SetArousal(-0.66f);
        emotions.SetValence(-0.5f);

        emotions.AddTrait(Trait::Aggressive);       
        emotions.AddTrait(Trait::Sad);

        emotions.SetMood(Mood::Relaxed);
        mCharacterState = emotions.GetEmotion();
        Character::name = "Dog";
        
    }

    glm::vec3 Dog::OnUpdate(Timestep deltaTime, TransformComponent& transform)
    {
        SetDeltaTime(deltaTime.GetSeconds());
        currentAffordanceLevel = BalanceRange(0, 1, currentAffordanceLevel);
        emotions.Update(deltaTime.GetSeconds());
        mFsm->update();

        if (spin)
        {
            transform.Rotation.y += 10 * GetDeltaTime();
        }


        if(hiss.m_Loaded)
            Audio::UpdateSound(hiss, transform);
        else if(hiss.GetStartLoad())
            hiss.m_Loaded = Audio::AddAudioSource(hiss);
        
        if(bark.m_Loaded)
            Audio::UpdateSound(bark, transform);
        else if(hiss.GetStartLoad())
            bark.m_Loaded = Audio::AddAudioSource(bark);

        TNAH_CORE_INFO("Are they loaded {0} {1}", hiss.m_Loaded, bark.m_Loaded);

        
        return targetPos;
    }

    std::pair<bool, bool> Dog::CheckAction(float affordanceValue, float distance, std::string tag)
    {
        std::pair<bool, bool> check;
        check.second = false;
        check.first = false;
        if (currentAffordanceLevel >= affordanceValue)
        {
            if (distance <= actionDistance)
            {
                switch (Character::GetDesiredAction())
                {
                case abuse:
                    if (canOutput)
                    {
                        switch (rand() % 3)
                        {
                        case 1:
                            LogAction("*Bark* I hate you! *Bark*", mColour);
                            break;
                        case 2:
                            LogAction("*Bark* Go away! *Bark*", mColour);
                            break;
                        default:
                            LogAction("*Bark* You stink! *Bark*", mColour);
                            break;
                        }
                        canOutput = false;

                        emotions.IncreaseArousal(0.5);
                        previousState = GetDesiredAction();
                    }
                    break;
                case greeting:
                    if (canOutput)
                    {
                        switch (rand() % 3)
                        {
                        case 1:
                            LogAction("*Bark* Hey! Come pet me! *Bark*", mColour);
                            break;
                        case 2:
                            LogAction("*Bark* Scratch my belly! *Bark*  ", mColour);
                            break;
                        default:
                            LogAction("*Bark* Good day for walkies ain't it! *Bark*", mColour);
                            break;
                        }
                        canOutput = false;

                        emotions.IncreaseArousal(0.5);
                        previousState = GetDesiredAction();
                    }
                    break;
                case sleep:
                    if (canOutput)
                    {
                        LogAction("*Bark* Nap Time! *Bark*", mColour);
                        emotions.DecreaseArousal(0.5);
                        emotions.IncreaseValence(0.5);
                        canOutput = false;
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

    float Dog::BalanceRange(float min, float max, float balanceValue)
    {
        if (balanceValue < min)
            return min;
        else if (balanceValue > max)
            return max;
    }

    void Dog::ApplyPlayerAction(PlayerActions givenAction)
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

    std::string Dog::CharacterString()
    {
        std::string str;
        str += "Name: Dog\nEmotion: " + emotions.GetCurrentEmotionAsString() + "\nMood: " + emotions.GetCurrentMoodAsString() +
            "\n" + emotions.GetTraitsAsString() +
            "\nArousal: " + std::to_string(emotions.GetArousal()) + "\nPositiveArousalMultiplier" + std::to_string(emotions.GetPositiveArosualMultiplier()) +
            "\nNegativeArousalMultiplier" + std::to_string(emotions.GetNegativeArousalMultiplier()) + "\nValence: " + std::to_string(emotions.GetValence()) +
            "\nPositiveValenceMultiplier" + std::to_string(emotions.GetPositiveArosualMultiplier()) + "\nNegativeValenceMultiplier"
            + std::to_string(emotions.GetNegativeValenceMultiplier()) + "\nAction: " + GetActionString(GetDesiredAction());
        return str;
    }

}
