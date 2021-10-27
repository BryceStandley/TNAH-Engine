#include "tnahpch.h"
#include "DogStates.h"

namespace tnah
{
    //Bird global
    void GlobalDog::Enter(Dog* owner)
    {
        //TNAH_CORE_INFO("Enter called");
    }

    void GlobalDog::Execute(Dog* owner)
    {
        auto emotion = owner->GetEmotions().GetEmotion();
        if (owner->mCharacterState != emotion)
        {
            switch (emotion)
            {
            case Emotion::Tense:
                owner->LogAction("Feeling Tense", owner->mColour);
                if (owner->mCharacterState != Emotion::Angry && owner->mCharacterState != Emotion::Frustrated)
                    owner->GetFsm()->changeState(&PissedOffStateDog::getInstance());
                break;
            case Emotion::Angry:
                owner->LogAction("Feeling Angry", owner->mColour);
                if (owner->mCharacterState != Emotion::Tense && owner->mCharacterState != Emotion::Frustrated)
                    owner->GetFsm()->changeState(&PissedOffStateDog::getInstance());
                break;
            case Emotion::Frustrated:
                owner->LogAction("Feeling Frustrated", owner->mColour);
                if (owner->mCharacterState != Emotion::Tense && owner->mCharacterState != Emotion::Angry)
                    owner->GetFsm()->changeState(&PissedOffStateDog::getInstance());
                break;
            case Emotion::Calm:
                owner->LogAction("Feeling Calm", owner->mColour);
                if (owner->mCharacterState != Emotion::Relaxed && owner->mCharacterState != Emotion::Content)
                    owner->GetFsm()->changeState(&ChillStateDog::getInstance());
                break;
            case Emotion::Content:
                owner->LogAction("Feeling Content", owner->mColour);
                if (owner->mCharacterState != Emotion::Calm && owner->mCharacterState != Emotion::Relaxed)
                    owner->GetFsm()->changeState(&ChillStateDog::getInstance());
                break;
            case Emotion::Relaxed:
                owner->LogAction("Feeling Relaxed", owner->mColour);
                if (owner->mCharacterState != Emotion::Calm && owner->mCharacterState != Emotion::Content)
                    owner->GetFsm()->changeState(&ChillStateDog::getInstance());
                break;
            case Emotion::Delighted:
                owner->LogAction("Feeling Delighted", owner->mColour);
                if (owner->mCharacterState != Emotion::Happy && owner->mCharacterState != Emotion::Excited)
                    owner->GetFsm()->changeState(&HappyStateDog::getInstance());
                break;
            case Emotion::Excited:
                owner->LogAction("Feeling Exited", owner->mColour);
                if (owner->mCharacterState != Emotion::Happy && owner->mCharacterState != Emotion::Delighted)
                    owner->GetFsm()->changeState(&HappyStateDog::getInstance());
                break;
            case Emotion::Happy:
                owner->LogAction("Feeling Happy", owner->mColour);
                if (owner->mCharacterState != Emotion::Excited && owner->mCharacterState != Emotion::Delighted)
                    owner->GetFsm()->changeState(&HappyStateDog::getInstance());
                break;
            case Emotion::Tired:
                owner->LogAction("Feeling tired", owner->mColour);
                if (owner->mCharacterState != Emotion::Bored && owner->mCharacterState != Emotion::Depressed)
                    owner->GetFsm()->changeState(&SadStateDog::getInstance());
                break;
            case Emotion::Bored:
                owner->LogAction("Feeling Bored", owner->mColour);
                if (owner->mCharacterState != Emotion::Tired && owner->mCharacterState != Emotion::Depressed)
                    owner->GetFsm()->changeState(&SadStateDog::getInstance());
                break;
            case Emotion::Depressed:
                owner->LogAction("Feeling Depressed", owner->mColour);
                if (owner->mCharacterState != Emotion::Tired && owner->mCharacterState != Emotion::Bored)
                    owner->GetFsm()->changeState(&SadStateDog::getInstance());
                break;
            default:
                owner->SetDesiredAction(sit);
                break;
            }

            owner->mCharacterState = emotion;
        }
        else
        {

        }

    }

    void GlobalDog::Exit(Dog* owner)
    {

    }

    void HappyDog::Enter(Dog* owner)
    {
       // 
    }

    void HappyDog::Execute(Dog* owner)
    {
        auto emotion = owner->GetEmotions().GetEmotion();

        switch (emotion)
        {
        case Emotion::Happy:
            owner->SetDesiredAction(Actions::greeting);
            owner->SetActionDistance(7.0f);
            owner->SetAffordanceLevel(0.1f);
            owner->spin = false;
            break;
        case Emotion::Delighted:
            owner->SetDesiredAction(Actions::greeting);
            owner->SetActionDistance(5.0f);
            owner->SetAffordanceLevel(1.0f);
            owner->spin = false;
            break;
        case Emotion::Excited:
            owner->SetDesiredAction(Actions::greeting);
            owner->SetActionDistance(9.0f);
            owner->SetAffordanceLevel(0.5f);
            owner->spin = true;
            break;
        default:
            break;
        }
    }

    void HappyDog::Exit(Dog* owner)
    {
        owner->spin = false;
        owner->canOutput = true;
    }

    void ChillDog::Enter(Dog* owner)
    {

    }

    void ChillDog::Execute(Dog* owner)
    {
        auto emotion = owner->GetEmotions().GetEmotion();

        switch (emotion)
        {
        case Emotion::Content:
            owner->SetDesiredAction(Actions::none);
            break;
        case Emotion::Relaxed:
            owner->SetDesiredAction(Actions::none);
            break;
        case Emotion::Calm:
            owner->SetDesiredAction(Actions::none);
            break;
        }
    }

    void ChillDog::Exit(Dog* owner)
    {

    }

    void PissedOffDog::Enter(Dog* owner)
    {
        owner->canOutput = true;
    }

    void PissedOffDog::Execute(Dog* owner)
    {
        auto emotion = owner->GetEmotions().GetEmotion();

        switch (emotion)
        {
        case Emotion::Frustrated:
            owner->SetDesiredAction(Actions::kick);
            owner->SetActionDistance(3.0f);
            owner->SetAffordanceLevel(1.0f);
            break;
        case Emotion::Angry:
            owner->SetDesiredAction(Actions::kick);
            owner->SetActionDistance(5.0f);
            owner->SetAffordanceLevel(0.5f);
            break;
        case Emotion::Tense:
            owner->SetDesiredAction(Actions::abuse);
            owner->SetActionDistance(7.0f);
            owner->SetAffordanceLevel(0.1f);
            break;
        default:
            break;
        }
    }

    void PissedOffDog::Exit(Dog* owner)
    {
        owner->canOutput = true;
    }

    void SadDog::Enter(Dog* owner){}

    void SadDog::Execute(Dog* owner)
    {
        auto emotion = owner->GetEmotions().GetEmotion();

        switch (emotion)
        {
        case Emotion::Depressed:
            owner->SetActionDistance(3.0f);
            owner->SetAffordanceLevel(0);
            break;
        case Emotion::Bored:
            //owner->SetDesiredAction(Actions::sleep);
            owner->SetActionDistance(5.0f);
            owner->SetAffordanceLevel(1.0f);
            break;
        case Emotion::Tired:
            owner->SetDesiredAction(Actions::sleep);
            owner->SetActionDistance(1.0f);
            owner->SetAffordanceLevel(1.0f);
            break;
        default:
            break;
        }
    }

    void SadDog::Exit(Dog* owner)
    {
        owner->canOutput = true;
    }
}
