#include "DogStates.h"

    void GlobalDog::Enter(Dog* owner)
    {
        //TNAH_INFO("Enter called");
    }

    void GlobalDog::Execute(Dog* owner)
    {
        auto emotion = owner->GetEmotions().GetEmotion();
        if (owner->GetCharacterState() != emotion)
        {
            switch (emotion)
            {
            case tnah::Emotion::Tense:
                owner->LogAction("Feeling Tense", owner->GetColour());
                if (owner->GetCharacterState() != tnah::Emotion::Angry && owner->GetCharacterState() != tnah::Emotion::Frustrated)
                    owner->GetFsm()->changeState(&AngryStateDog::getInstance());
                break;
            case tnah::Emotion::Angry:
                owner->LogAction("Feeling Angry", owner->GetColour());
                if (owner->GetCharacterState() != tnah::Emotion::Tense && owner->GetCharacterState() != tnah::Emotion::Frustrated)
                    owner->GetFsm()->changeState(&AngryStateDog::getInstance());
                break;
            case tnah::Emotion::Frustrated:
                owner->LogAction("Feeling Frustrated", owner->GetColour());
                if (owner->GetCharacterState() != tnah::Emotion::Tense && owner->GetCharacterState() != tnah::Emotion::Angry)
                    owner->GetFsm()->changeState(&AngryStateDog::getInstance());
                break;
            case tnah::Emotion::Calm:
                owner->LogAction("Feeling Calm", owner->GetColour());
                if (owner->GetCharacterState() != tnah::Emotion::Relaxed && owner->GetCharacterState() != tnah::Emotion::Content)
                    owner->GetFsm()->changeState(&ChillStateDog::getInstance());
                break;
            case tnah::Emotion::Content:
                owner->LogAction("Feeling Content", owner->GetColour());
                if (owner->GetCharacterState() != tnah::Emotion::Calm && owner->GetCharacterState() != tnah::Emotion::Relaxed)
                    owner->GetFsm()->changeState(&ChillStateDog::getInstance());
                break;
            case tnah::Emotion::Relaxed:
                owner->LogAction("Feeling Relaxed", owner->GetColour());
                if (owner->GetCharacterState() != tnah::Emotion::Calm && owner->GetCharacterState() != tnah::Emotion::Content)
                    owner->GetFsm()->changeState(&ChillStateDog::getInstance());
                break;
            case tnah::Emotion::Delighted:
                owner->LogAction("Feeling Delighted", owner->GetColour());
                if (owner->GetCharacterState() != tnah::Emotion::Happy && owner->GetCharacterState() != tnah::Emotion::Excited)
                    owner->GetFsm()->changeState(&HappyStateDog::getInstance());
                break;
            case tnah::Emotion::Excited:
                owner->LogAction("Feeling Exited", owner->GetColour());
                if (owner->GetCharacterState() != tnah::Emotion::Happy && owner->GetCharacterState() != tnah::Emotion::Delighted)
                    owner->GetFsm()->changeState(&HappyStateDog::getInstance());
                break;
            case tnah::Emotion::Happy:
                owner->LogAction("Feeling Happy", owner->GetColour());
                if (owner->GetCharacterState() != tnah::Emotion::Excited && owner->GetCharacterState() != tnah::Emotion::Delighted)
                    owner->GetFsm()->changeState(&HappyStateDog::getInstance());
                break;
            case tnah::Emotion::Tired:
                owner->LogAction("Feeling tired", owner->GetColour());
                if (owner->GetCharacterState() != tnah::Emotion::Bored && owner->GetCharacterState() != tnah::Emotion::Depressed)
                    owner->GetFsm()->changeState(&SadStateDog::getInstance());
                break;
            case tnah::Emotion::Bored:
                owner->LogAction("Feeling Bored", owner->GetColour());
                if (owner->GetCharacterState() != tnah::Emotion::Tired && owner->GetCharacterState() != tnah::Emotion::Depressed)
                    owner->GetFsm()->changeState(&SadStateDog::getInstance());
                break;
            case tnah::Emotion::Depressed:
                owner->LogAction("Feeling Depressed", owner->GetColour());
                if (owner->GetCharacterState() != tnah::Emotion::Tired && owner->GetCharacterState() != tnah::Emotion::Bored)
                    owner->GetFsm()->changeState(&SadStateDog::getInstance());
                break;
            default:
                owner->SetDesiredAction(tnah::sit);
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
        owner->PutTimerDown();
    }

    void PosArousalPosValenceDog::Execute(Dog* owner)
    {
        auto emotion = owner->GetEmotions().GetEmotion();

        switch (emotion)
        {
        case tnah::Emotion::Happy:
            owner->SetDesiredAction(tnah::Actions::greeting);
            owner->SetActionDistance(7.0f);
            owner->SetAffordanceLevel(0.1f);
            owner->SetSpin(true);
            break;
        case tnah::Emotion::Delighted:
            owner->SetDesiredAction(tnah::Actions::greeting);
            owner->SetActionDistance(5.0f);
            owner->SetAffordanceLevel(1.0f);
            owner->SetSpin(true);
            break;
        case tnah::Emotion::Excited:
            owner->SetDesiredAction(tnah::Actions::greeting);
            owner->SetActionDistance(9.0f);
            owner->SetAffordanceLevel(0.5f);
            owner->SetSpin(true);
            break;
        default:
            break;
        }
    }

    void PosArousalPosValenceDog::Exit(Dog* owner)
    {
        owner->SetSpin(false);
        owner->Stopbark();
    }

    void NegArousalPosValenceDog::Enter(Dog* owner)
    {
        owner->GetEmotions().UpdateTimer();
        owner->PutTimerDown();
    }

    void NegArousalPosValenceDog::Execute(Dog* owner)
    {
        auto emotion = owner->GetEmotions().GetEmotion();

        switch (emotion)
        {
        case tnah::Emotion::Content:
            owner->SetDesiredAction(tnah::Actions::none);
            break;
        case tnah::Emotion::Relaxed:
            owner->SetDesiredAction(tnah::Actions::none);
            break;
        case tnah::Emotion::Calm:
            owner->SetDesiredAction(tnah::Actions::none);
            break;
        default:
            break;
        }
    }

    void NegArousalPosValenceDog::Exit(Dog* owner)
    {

    }

    void PosArousalNegValenceDog::Enter(Dog* owner)
    {
        owner->GetEmotions().UpdateTimer();
        owner->ShootHiss();
        owner->PutTimerDown();
    }

    void PosArousalNegValenceDog::Execute(Dog* owner)
    {
        auto emotion = owner->GetEmotions().GetEmotion();
        switch (emotion)
        {
        case tnah::Emotion::Frustrated:
            owner->SetDesiredAction(tnah::Actions::abuse);
            owner->SetActionDistance(5.0f);
            owner->SetAffordanceLevel(1.0f);
            break;
        case tnah::Emotion::Angry:
            owner->SetDesiredAction(tnah::Actions::abuse);
            owner->SetActionDistance(5.0f);
            owner->SetAffordanceLevel(0.5f);
            break;
        case tnah::Emotion::Tense:
            owner->SetDesiredAction(tnah::Actions::abuse);
            owner->SetActionDistance(7.0f);
            owner->SetAffordanceLevel(0.1f);
            break;
        default:
            break;
        }
        
    }

    void PosArousalNegValenceDog::Exit(Dog* owner)
    {
        owner->StopHiss();
    }

    void NegArousalNegValenceDog::Enter(Dog* owner)
    {
        owner->GetEmotions().UpdateTimer();
        owner->PutTimerDown();
    }

    void NegArousalNegValenceDog::Execute(Dog* owner)
    {
        auto emotion = owner->GetEmotions().GetEmotion();

        switch (emotion)
        {
        case tnah::Emotion::Depressed:
            owner->SetDesiredAction(tnah::Actions::sleep);
            owner->SetActionDistance(3.0f);
            owner->SetAffordanceLevel(0.1f);
            break;
        case tnah::Emotion::Bored:
            owner->SetDesiredAction(tnah::Actions::sleep);
            owner->SetActionDistance(1.0f);
            owner->SetAffordanceLevel(1.0f);
            break;
        case tnah::Emotion::Tired:
            owner->SetDesiredAction(tnah::Actions::sleep);
            owner->SetActionDistance(1.0f);
            owner->SetAffordanceLevel(1.0f);
            break;
        default:
            break;
        }
    }

    void NegArousalNegValenceDog::Exit(Dog* owner)
    {
        
    }
