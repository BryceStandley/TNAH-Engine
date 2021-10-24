#include "tnahpch.h"
#include "BirdStates.h"

namespace tnah
{
    //Bird global
    void GlobalBird::Enter(Bird* owner)
    {
        //TNAH_CORE_INFO("Enter called");
    }

    void GlobalBird::Execute(Bird* owner)
    {
        auto emotion = owner->GetEmotions().GetEmotion();
        if (owner->mCharacterState != emotion)
        {
            switch (emotion)
            {
            case Emotion::Tense:
                owner->LogAction("Feeling Tense", owner->mColour);
                if (owner->mCharacterState != Emotion::Angry || owner->mCharacterState != Emotion::Frustrated)
                    owner->GetFsm()->changeState(&PissedOffStateBird::getInstance());
                break;
            case Emotion::Angry:
                owner->LogAction("Feeling Angry", owner->mColour);
                if (owner->mCharacterState != Emotion::Tense || owner->mCharacterState != Emotion::Frustrated)
                    owner->GetFsm()->changeState(&PissedOffStateBird::getInstance());
                break;
            case Emotion::Frustrated:
                owner->LogAction("Feeling Frustrated", owner->mColour);
                if (owner->mCharacterState != Emotion::Tense || owner->mCharacterState != Emotion::Angry)
                    owner->GetFsm()->changeState(&PissedOffStateBird::getInstance());
                break;
            case Emotion::Calm:
                owner->LogAction("Feeling Calm", owner->mColour);
                if (owner->mCharacterState != Emotion::Relaxed || owner->mCharacterState != Emotion::Content)
                    owner->GetFsm()->changeState(&ChillStateBird::getInstance());
                break;
            case Emotion::Content:
                owner->LogAction("Feeling Content", owner->mColour);
                if (owner->mCharacterState != Emotion::Calm || owner->mCharacterState != Emotion::Relaxed)
                    owner->GetFsm()->changeState(&ChillStateBird::getInstance());
                break;
            case Emotion::Relaxed:
                owner->LogAction("Feeling Relaxed", owner->mColour);
                if (owner->mCharacterState != Emotion::Calm || owner->mCharacterState != Emotion::Content)
                    owner->GetFsm()->changeState(&ChillStateBird::getInstance());
                break;
            case Emotion::Delighted:
                owner->LogAction("Feeling Delighted", owner->mColour);
                if (owner->mCharacterState != Emotion::Happy || owner->mCharacterState != Emotion::Excited)
                    owner->GetFsm()->changeState(&HappyStateBird::getInstance());
                break;
            case Emotion::Excited:
                owner->LogAction("Feeling Exited", owner->mColour);
                if (owner->mCharacterState != Emotion::Happy || owner->mCharacterState != Emotion::Delighted)
                    owner->GetFsm()->changeState(&HappyStateBird::getInstance());
                break;
            case Emotion::Happy:
                owner->LogAction("Feeling Happy", owner->mColour);
                if (owner->mCharacterState != Emotion::Excited || owner->mCharacterState != Emotion::Delighted)
                    owner->GetFsm()->changeState(&HappyStateBird::getInstance());
                break;
            case Emotion::Tired:
                owner->LogAction("Feeling tired", owner->mColour);
                if (owner->mCharacterState != Emotion::Bored || owner->mCharacterState != Emotion::Depressed)
                    owner->GetFsm()->changeState(&SadStateBird::getInstance());
                break;
            case Emotion::Bored:
                owner->LogAction("Feeling Bored", owner->mColour);
                if (owner->mCharacterState != Emotion::Tired || owner->mCharacterState != Emotion::Depressed)
                    owner->GetFsm()->changeState(&SadStateBird::getInstance());
                break;
            case Emotion::Depressed:
                owner->LogAction("Feeling Depressed", owner->mColour);
                if (owner->mCharacterState != Emotion::Tired || owner->mCharacterState != Emotion::Bored)
                    owner->GetFsm()->changeState(&SadStateBird::getInstance());
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

    void GlobalBird::Exit(Bird* owner)
    {

    }

    void HappyBird::Enter(Bird* owner)
    {
        owner->SetWander(true);
    }

    void HappyBird::Execute(Bird* owner)
    {
        auto emotion = owner->GetEmotions().GetEmotion();

        switch (emotion)
        {
        case Emotion::Happy:
            owner->SetDesiredAction(Actions::greeting);
            owner->SetActionDistance(7.0f);
            owner->SetAffordanceLevel(0.1f);
           // owner->spin = false;
            break;
        case Emotion::Delighted:
            owner->SetDesiredAction(Actions::greeting);
            owner->SetActionDistance(5.0f);
            owner->SetAffordanceLevel(1.0f);
            //owner->spin = false;
            break;
        case Emotion::Excited:
            owner->SetDesiredAction(Actions::greeting);
            owner->SetActionDistance(9.0f);
            owner->SetAffordanceLevel(0.5f);
            //owner->spin = true;
            break;
        default:
            break;
        }
    }

    void HappyBird::Exit(Bird* owner)
    {
        //owner->spin = false;
        owner->SetWander(false);
        owner->canOutput = true;
    }

    void ChillBird::Enter(Bird* owner)
    {

    }

    void ChillBird::Execute(Bird* owner)
    {
        //Heads home to idle
    }

    void ChillBird::Exit(Bird* owner)
    {

    }

    void PissedOffBird::Enter(Bird* owner)
    {
        owner->SetWander(true);
        owner->SetSpeed(1.5f);
        owner->canOutput = true;
    }

    void PissedOffBird::Execute(Bird* owner)
    {
        auto emotion = owner->GetEmotions().GetEmotion();

        switch (emotion)
        {
        case Emotion::Frustrated:
            owner->SetDesiredAction(Actions::pickup);
            owner->SetActionDistance(3.0f);
            owner->SetAffordanceLevel(1.0f);
            owner->SetSpeed(1.5f);
            break;
        case Emotion::Angry:
            owner->SetDesiredAction(Actions::pickup);
            owner->SetActionDistance(5.0f);
            owner->SetAffordanceLevel(0.5f);
            owner->SetSpeed(2.0f);
            break;
        case Emotion::Tense:
            owner->SetDesiredAction(Actions::abuse);
            owner->SetActionDistance(7.0f);
            owner->SetAffordanceLevel(0.1f);
            owner->SetSpeed(2.5f);
            break;
        default:
            break;
        }
    }

    void PissedOffBird::Exit(Bird* owner)
    {
        owner->SetWander(false);
        owner->SetSpeed(1.0f);
        owner->canOutput = true;
    }

    void SadBird::Enter(Bird* owner)
    {
        owner->SetWander(true);
        owner->SetSpeed(0.75f);
    }

    void SadBird::Execute(Bird* owner)
    {
        auto emotion = owner->GetEmotions().GetEmotion();

        switch (emotion)
        {
        case Emotion::Depressed:
            owner->SetDesiredAction(Actions::pickup);
            owner->SetActionDistance(3.0f);
            owner->SetAffordanceLevel(0.5f);
            owner->SetSpeed(0.75f);
            break;
        case Emotion::Bored:
            owner->SetDesiredAction(Actions::pickup);
            owner->SetActionDistance(5.0f);
            owner->SetAffordanceLevel(0.1f);
            owner->SetSpeed(0.6f);
            break;
        case Emotion::Tired:
            owner->SetDesiredAction(Actions::sleep);
            owner->SetActionDistance(3.0f);
            owner->SetAffordanceLevel(1.0f);
            owner->SetSpeed(0.5f);
            break;
        default:
            break;
        }
    }

    void SadBird::Exit(Bird* owner)
    {
        owner->SetWander(false);
        owner->SetSpeed(1.0f);
        owner->canOutput = true;
    }
}
