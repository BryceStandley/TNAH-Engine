#include "tnahpch.h"
#include "StudentStates.h"

namespace tnah
{
    //Student global
    void GlobalStudent::Enter(Student* owner)
    {
        //TNAH_CORE_INFO("Enter called");
    }

    void GlobalStudent::Execute(Student* owner)
    {
        auto emotion = owner->GetEmotions().GetEmotion();
        if (owner->mCharacterState != emotion)
        {
            switch (emotion)
            {
            case Emotion::Tense:
                owner->LogAction("Feeling Tense", owner->mColour);
                if (owner->mCharacterState != Emotion::Angry && owner->mCharacterState != Emotion::Frustrated)
                    owner->GetFsm()->changeState(&PissedOffStateStudent::getInstance());
                break;
            case Emotion::Angry:
                owner->LogAction("Feeling Angry", owner->mColour);
                if (owner->mCharacterState != Emotion::Tense && owner->mCharacterState != Emotion::Frustrated)
                    owner->GetFsm()->changeState(&PissedOffStateStudent::getInstance());
                break;
            case Emotion::Frustrated:
                owner->LogAction("Feeling Frustrated", owner->mColour);
                if (owner->mCharacterState != Emotion::Tense && owner->mCharacterState != Emotion::Angry)
                    owner->GetFsm()->changeState(&PissedOffStateStudent::getInstance());
                break;
            case Emotion::Calm:
                owner->LogAction("Feeling Calm", owner->mColour);
                if (owner->mCharacterState != Emotion::Relaxed && owner->mCharacterState != Emotion::Content)
                    owner->GetFsm()->changeState(&ChillStateStudent::getInstance());
                break;
            case Emotion::Content:
                owner->LogAction("Feeling Content", owner->mColour);
                if (owner->mCharacterState != Emotion::Calm && owner->mCharacterState != Emotion::Relaxed)
                    owner->GetFsm()->changeState(&ChillStateStudent::getInstance());
                break;
            case Emotion::Relaxed:
                owner->LogAction("Feeling Relaxed", owner->mColour);
                if (owner->mCharacterState != Emotion::Calm && owner->mCharacterState != Emotion::Content)
                    owner->GetFsm()->changeState(&ChillStateStudent::getInstance());
                break;
            case Emotion::Delighted:
                owner->LogAction("Feeling Delighted", owner->mColour);
                if (owner->mCharacterState != Emotion::Happy && owner->mCharacterState != Emotion::Excited)
                    owner->GetFsm()->changeState(&HappyStateStudent::getInstance());
                break;
            case Emotion::Excited:
                owner->LogAction("Feeling Exited", owner->mColour);
                if (owner->mCharacterState != Emotion::Happy && owner->mCharacterState != Emotion::Delighted)
                    owner->GetFsm()->changeState(&HappyStateStudent::getInstance());
                break;
            case Emotion::Happy:
                owner->LogAction("Feeling Happy", owner->mColour);
                if (owner->mCharacterState != Emotion::Excited && owner->mCharacterState != Emotion::Delighted)
                    owner->GetFsm()->changeState(&HappyStateStudent::getInstance());
                break;
            case Emotion::Tired:
                owner->LogAction("Feeling tired", owner->mColour);
                if (owner->mCharacterState != Emotion::Bored && owner->mCharacterState != Emotion::Depressed)
                    owner->GetFsm()->changeState(&SadStateStudent::getInstance());
                break;
            case Emotion::Bored:
                owner->LogAction("Feeling Bored", owner->mColour);
                if (owner->mCharacterState != Emotion::Tired && owner->mCharacterState != Emotion::Depressed)
                    owner->GetFsm()->changeState(&SadStateStudent::getInstance());
                break;
            case Emotion::Depressed:
                owner->LogAction("Feeling Depressed", owner->mColour);
                if (owner->mCharacterState != Emotion::Tired && owner->mCharacterState != Emotion::Bored)
                    owner->GetFsm()->changeState(&SadStateStudent::getInstance());
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

    void GlobalStudent::Exit(Student* owner)
    {

    }

    void HappyStudent::Enter(Student* owner)
    {
        owner->SetWander(true);
    }

    void HappyStudent::Execute(Student* owner)
    {
        auto emotion = owner->GetEmotions().GetEmotion();

        switch (emotion)
        {
        case Emotion::Happy:
            owner->SetDesiredAction(Actions::drink);
            owner->SetActionDistance(1.0f);
            owner->SetAffordanceLevel(1.0f);
            owner->SetSpeed(1.0f);
            // owner->spin = false;
            break;
        case Emotion::Delighted:
            owner->SetDesiredAction(Actions::greeting);
            owner->SetActionDistance(5.0f);
            owner->SetAffordanceLevel(1.0f);
            owner->SetSpeed(1.5f);
            //owner->spin = false;
            break;
        case Emotion::Excited:
            owner->SetDesiredAction(Actions::drink);
            owner->SetActionDistance(1.0f);
            owner->SetAffordanceLevel(1.0f);
            owner->SetSpeed(2.0f);
            //owner->spin = true;
            break;
        default:
            break;
        }
    }

    void HappyStudent::Exit(Student* owner)
    {
        //owner->spin = false;
        owner->SetWander(false);
        owner->canOutput = true;
        owner->SetSpeed(1.0f);
    }

    void ChillStudent::Enter(Student* owner)
    {
        owner->SetWander(true);
    }

    void ChillStudent::Execute(Student* owner)
    {
        auto emotion = owner->GetEmotions().GetEmotion();
        if(owner->canOutput)
            owner->SetWander(true);
        
        switch (emotion)
        {
        case Emotion::Content:
            owner->SetDesiredAction(Actions::sit);
            owner->SetActionDistance(1.0f);
            owner->SetAffordanceLevel(1.0f);
            // owner->spin = false;
            break;
        case Emotion::Relaxed:
            owner->SetDesiredAction(Actions::sit);
            owner->SetActionDistance(1.0f);
            owner->SetAffordanceLevel(1.0f);
            //owner->spin = false;
            break;
        case Emotion::Calm:
            owner->SetDesiredAction(Actions::none);
            owner->SetActionDistance(1.0f);
            owner->SetAffordanceLevel(0.1f);
            //owner->spin = true;
            break;
        default:
            break;
        }
    }

    void ChillStudent::Exit(Student* owner)
    {
        owner->SetWander(false);
    }

    void PissedOffStudent::Enter(Student* owner)
    {
        owner->SetWander(true);
        owner->SetSpeed(1.5f);
        owner->canOutput = true;
    }

    void PissedOffStudent::Execute(Student* owner)
    {
        auto emotion = owner->GetEmotions().GetEmotion();

        switch (emotion)
        {
        case Emotion::Frustrated:
            owner->SetDesiredAction(Actions::kick);
            owner->SetActionDistance(1.0f);
            owner->SetAffordanceLevel(1.0f);
            owner->SetSpeed(1.5f);
            break;
        case Emotion::Angry:
            owner->SetDesiredAction(Actions::kick);
            owner->SetActionDistance(2.0f);
            owner->SetAffordanceLevel(0.5f);
            owner->SetSpeed(2.0f);
            break;
        case Emotion::Tense:
            owner->SetDesiredAction(Actions::kick);
            owner->SetActionDistance(3.0f);
            owner->SetAffordanceLevel(0.1f);
            owner->SetSpeed(3.0f);
            break;
        default:
            break;
        }
    }

    void PissedOffStudent::Exit(Student* owner)
    {
        owner->SetWander(false);
        owner->SetSpeed(1.0f);
        owner->canOutput = true;
    }

    void SadStudent::Enter(Student* owner)
    {
        owner->SetWander(true);
        owner->SetSpeed(0.75f);
    }

    void SadStudent::Execute(Student* owner)
    {
        auto emotion = owner->GetEmotions().GetEmotion();

        if(owner->canOutput)
            owner->SetWander(true);
        
        switch (emotion)
        {
        case Emotion::Depressed:
            owner->SetDesiredAction(Actions::none);
            owner->SetActionDistance(5.0f);
            owner->SetAffordanceLevel(0.0f);
            owner->SetSpeed(0.25f);
            break;
        case Emotion::Bored:
            owner->SetDesiredAction(Actions::play);
            owner->SetActionDistance(2.0f);
            owner->SetAffordanceLevel(0.5f);
            owner->SetSpeed(0.75f);
            break;
        case Emotion::Tired:
            owner->SetDesiredAction(Actions::sleep);
            owner->SetActionDistance(3.0f);
            owner->SetAffordanceLevel(0.1f);
            owner->SetSpeed(0.5f);
            break;
        default:
            break;
        }
    }

    void SadStudent::Exit(Student* owner)
    {
        owner->SetWander(false);
        owner->SetSpeed(1.0f);
        owner->canOutput = true;
    }
}
