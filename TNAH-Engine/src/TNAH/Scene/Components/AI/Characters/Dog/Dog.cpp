#include "tnahpch.h"
#include "Dog.h"
#include "DogStates.h"

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
        mColour = glm::vec4(1, 0, 0, 0);
        currentAffordanceLevel = 1.0f;
        //Temporary stuff
        emotions.AddTrait(Trait::Aggressive);
        emotions.AddTrait(Trait::Sad);
        emotions.SetMood(Mood::Relaxed);
        mCharacterState = emotions.GetEmotion();
        Character::name = "dog";
        //mFsm->setCurrentState
    }

    glm::vec3 Dog::OnUpdate(Timestep deltaTime, TransformComponent& transform)
    {
        SetDeltaTime(deltaTime.GetSeconds());
        currentAffordanceLevel = BalanceRange(0, 1, currentAffordanceLevel);
        emotions.Update();
        mFsm->update();

        if (spin)
        {
            transform.Rotation.y += 10 * GetDeltaTime();
        }

        return targetPos;
    }

    bool Dog::CheckAction(float affordanceValue, float distance, std::string tag)
    {
        bool r = false;
        if (currentAffordanceLevel <= affordanceValue)
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

                        emotions.IncreaseArousal(0.25);
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

                        emotions.IncreaseArousal(0.2);
                        emotions.IncreaseValence(0.2);
                    }
                    break;
                case sleep:
                    if (canOutput)
                    {
                        LogAction("*Bark* Nap Time! *Bark*", mColour);
                        canOutput = false;
                    }
                    emotions.DecreaseArousal(0.1 * GetDeltaTime());
                    emotions.IncreaseValence(0.2 * GetDeltaTime());
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