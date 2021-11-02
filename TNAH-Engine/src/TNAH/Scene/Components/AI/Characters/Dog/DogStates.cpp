#include "tnahpch.h"
#include "DogStates.h"

namespace tnah
{
    void GlobalDog::Enter(Dog* owner)
    {
        //TNAH_CORE_INFO("Enter called");
    }

    void GlobalDog::Execute(Dog* owner)
    {
        auto emotion = owner->GetEmotions().GetEmotion();
        if (owner->GetCharacterState() != emotion)
        {
            switch (emotion)
            {
            case Emotion::Tense:
                owner->LogAction("Feeling Tense", owner->GetColour());
                if (owner->GetCharacterState() != Emotion::Angry && owner->GetCharacterState() != Emotion::Frustrated)
                    owner->GetFsm()->changeState(&AngryStateDog::getInstance());
                break;
            case Emotion::Angry:
                owner->LogAction("Feeling Angry", owner->GetColour());
                if (owner->GetCharacterState() != Emotion::Tense && owner->GetCharacterState() != Emotion::Frustrated)
                    owner->GetFsm()->changeState(&AngryStateDog::getInstance());
                break;
            case Emotion::Frustrated:
                owner->LogAction("Feeling Frustrated", owner->GetColour());
                if (owner->GetCharacterState() != Emotion::Tense && owner->GetCharacterState() != Emotion::Angry)
                    owner->GetFsm()->changeState(&AngryStateDog::getInstance());
                break;
            case Emotion::Calm:
                owner->LogAction("Feeling Calm", owner->GetColour());
                if (owner->GetCharacterState() != Emotion::Relaxed && owner->GetCharacterState() != Emotion::Content)
                    owner->GetFsm()->changeState(&ChillStateDog::getInstance());
                break;
            case Emotion::Content:
                owner->LogAction("Feeling Content", owner->GetColour());
                if (owner->GetCharacterState() != Emotion::Calm && owner->GetCharacterState() != Emotion::Relaxed)
                    owner->GetFsm()->changeState(&ChillStateDog::getInstance());
                break;
            case Emotion::Relaxed:
                owner->LogAction("Feeling Relaxed", owner->GetColour());
                if (owner->GetCharacterState() != Emotion::Calm && owner->GetCharacterState() != Emotion::Content)
                    owner->GetFsm()->changeState(&ChillStateDog::getInstance());
                break;
            case Emotion::Delighted:
                owner->LogAction("Feeling Delighted", owner->GetColour());
                if (owner->GetCharacterState() != Emotion::Happy && owner->GetCharacterState() != Emotion::Excited)
                    owner->GetFsm()->changeState(&HappyStateDog::getInstance());
                break;
            case Emotion::Excited:
                owner->LogAction("Feeling Exited", owner->GetColour());
                if (owner->GetCharacterState() != Emotion::Happy && owner->GetCharacterState() != Emotion::Delighted)
                    owner->GetFsm()->changeState(&HappyStateDog::getInstance());
                break;
            case Emotion::Happy:
                owner->LogAction("Feeling Happy", owner->GetColour());
                if (owner->GetCharacterState() != Emotion::Excited && owner->GetCharacterState() != Emotion::Delighted)
                    owner->GetFsm()->changeState(&HappyStateDog::getInstance());
                break;
            case Emotion::Tired:
                owner->LogAction("Feeling tired", owner->GetColour());
                if (owner->GetCharacterState() != Emotion::Bored && owner->GetCharacterState() != Emotion::Depressed)
                    owner->GetFsm()->changeState(&SadStateDog::getInstance());
                break;
            case Emotion::Bored:
                owner->LogAction("Feeling Bored", owner->GetColour());
                if (owner->GetCharacterState() != Emotion::Tired && owner->GetCharacterState() != Emotion::Depressed)
                    owner->GetFsm()->changeState(&SadStateDog::getInstance());
                break;
            case Emotion::Depressed:
                owner->LogAction("Feeling Depressed", owner->GetColour());
                if (owner->GetCharacterState() != Emotion::Tired && owner->GetCharacterState() != Emotion::Bored)
                    owner->GetFsm()->changeState(&SadStateDog::getInstance());
                break;
            default:
                owner->SetDesiredAction(sit);
                break;
            }

            owner->SetCharacterState(emotion);
        }
        else
        {

        }

    }

    void GlobalDog::Exit(Dog* owner)
    {

    }

    void PosArousalPosValenceDog::Enter(Dog* owner)
    {
        owner->GetEmotions().UpdateTimer();
        owner->Shootbark();
    }

    void PosArousalPosValenceDog::Execute(Dog* owner)
    {
        auto emotion = owner->GetEmotions().GetEmotion();

        switch (emotion)
        {
        case Emotion::Happy:
            owner->SetDesiredAction(Actions::greeting);
            owner->SetActionDistance(7.0f);
            owner->SetAffordanceLevel(0.1f);
            owner->SetSpin(false);
            break;
        case Emotion::Delighted:
            owner->SetDesiredAction(Actions::greeting);
            owner->SetActionDistance(5.0f);
            owner->SetAffordanceLevel(1.0f);
            owner->SetSpin(false);
            break;
        case Emotion::Excited:
            owner->SetDesiredAction(Actions::greeting);
            owner->SetActionDistance(9.0f);
            owner->SetAffordanceLevel(0.5f);
            owner->SetSpin(false);
            break;
        default:
            break;
        }
    }

    void PosArousalPosValenceDog::Exit(Dog* owner)
    {
        owner->SetSpin(false);
        owner->SetCanOutput(true);
        owner->Stopbark();
    }

    void NegArousalPosValenceDog::Enter(Dog* owner)
    {
        owner->GetEmotions().UpdateTimer();
    }

    void NegArousalPosValenceDog::Execute(Dog* owner)
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

    void NegArousalPosValenceDog::Exit(Dog* owner)
    {

    }

    void PosArousalNegValenceDog::Enter(Dog* owner)
    {
        owner->GetEmotions().UpdateTimer();
        owner->SetCanOutput(true);
        owner->ShootHiss();
    }

    void PosArousalNegValenceDog::Execute(Dog* owner)
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

    void PosArousalNegValenceDog::Exit(Dog* owner)
    {
        owner->SetCanOutput(true);
        owner->StopHiss();
    }

    void NegArousalNegValenceDog::Enter(Dog* owner)
    {
        owner->GetEmotions().UpdateTimer();
    }

    void NegArousalNegValenceDog::Execute(Dog* owner)
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

    void NegArousalNegValenceDog::Exit(Dog* owner)
    {
        owner->SetCanOutput(true);
    }
}
