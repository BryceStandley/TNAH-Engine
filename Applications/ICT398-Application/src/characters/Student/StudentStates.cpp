#include "StudentStates.h"

    //Student global
    void GlobalStudent::Enter(Student* owner)
    {
        //TNAH_CORE_INFO("Enter called");
    }

    void GlobalStudent::Execute(Student* owner)
    {
        auto emotion = owner->GetEmotions().GetEmotion();
        if (owner->GetCharacterState() != emotion)
        {
            switch (emotion)
            {
            case Emotion::Tense:
                owner->LogAction("Feeling Tense", owner->GetColour());
                if (owner->GetCharacterState() != Emotion::Angry && owner->GetCharacterState() != Emotion::Frustrated)
                    owner->GetFsm()->changeState(&PissedOffStateStudent::getInstance());
                break;
            case Emotion::Angry:
                owner->LogAction("Feeling Angry", owner->GetColour());
                if (owner->GetCharacterState() != Emotion::Tense && owner->GetCharacterState() != Emotion::Frustrated)
                    owner->GetFsm()->changeState(&PissedOffStateStudent::getInstance());
                break;
            case Emotion::Frustrated:
                owner->LogAction("Feeling Frustrated", owner->GetColour());
                if (owner->GetCharacterState() != Emotion::Tense && owner->GetCharacterState() != Emotion::Angry)
                    owner->GetFsm()->changeState(&PissedOffStateStudent::getInstance());
                break;
            case Emotion::Calm:
                owner->LogAction("Feeling Calm", owner->GetColour());
                if (owner->GetCharacterState() != Emotion::Relaxed && owner->GetCharacterState() != Emotion::Content)
                    owner->GetFsm()->changeState(&ChillStateStudent::getInstance());
                break;
            case Emotion::Content:
                owner->LogAction("Feeling Content", owner->GetColour());
                if (owner->GetCharacterState() != Emotion::Calm && owner->GetCharacterState() != Emotion::Relaxed)
                    owner->GetFsm()->changeState(&ChillStateStudent::getInstance());
                break;
            case Emotion::Relaxed:
                owner->LogAction("Feeling Relaxed", owner->GetColour());
                if (owner->GetCharacterState() != Emotion::Calm && owner->GetCharacterState() != Emotion::Content)
                    owner->GetFsm()->changeState(&ChillStateStudent::getInstance());
                break;
            case Emotion::Delighted:
                owner->LogAction("Feeling Delighted", owner->GetColour());
                if (owner->GetCharacterState() != Emotion::Happy && owner->GetCharacterState() != Emotion::Excited)
                    owner->GetFsm()->changeState(&HappyStateStudent::getInstance());
                break;
            case Emotion::Excited:
                owner->LogAction("Feeling Exited", owner->GetColour());
                if (owner->GetCharacterState() != Emotion::Happy && owner->GetCharacterState() != Emotion::Delighted)
                    owner->GetFsm()->changeState(&HappyStateStudent::getInstance());
                break;
            case Emotion::Happy:
                owner->LogAction("Feeling Happy", owner->GetColour());
                if (owner->GetCharacterState() != Emotion::Excited && owner->GetCharacterState() != Emotion::Delighted)
                    owner->GetFsm()->changeState(&HappyStateStudent::getInstance());
                break;
            case Emotion::Tired:
                owner->LogAction("Feeling tired", owner->GetColour());
                if (owner->GetCharacterState() != Emotion::Bored && owner->GetCharacterState() != Emotion::Depressed)
                    owner->GetFsm()->changeState(&SadStateStudent::getInstance());
                break;
            case Emotion::Bored:
                owner->LogAction("Feeling Bored", owner->GetColour());
                if (owner->GetCharacterState() != Emotion::Tired && owner->GetCharacterState() != Emotion::Depressed)
                    owner->GetFsm()->changeState(&SadStateStudent::getInstance());
                break;
            case Emotion::Depressed:
                owner->LogAction("Feeling Depressed", owner->GetColour());
                if (owner->GetCharacterState() != Emotion::Tired && owner->GetCharacterState() != Emotion::Bored)
                    owner->GetFsm()->changeState(&SadStateStudent::getInstance());
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

    void GlobalStudent::Exit(Student* owner)
    {

    }

    void PosArousalPosValenceStudent::Enter(Student* owner)
    {
        owner->GetEmotions().UpdateTimer();
        owner->SetWander(true);
        owner->PutTimerDown();
    }

    void PosArousalPosValenceStudent::Execute(Student* owner)
    {
        auto emotion = owner->GetEmotions().GetEmotion();

        switch (emotion)
        {
        case Emotion::Happy:
            owner->SetDesiredAction(Actions::drink);
            owner->SetActionDistance(1.0f);
            owner->SetAffordanceLevel(1.0f);
            owner->SetSpeed(1.0f);
            break;
        case Emotion::Delighted:
            owner->SetDesiredAction(Actions::greeting);
            owner->SetActionDistance(5.0f);
            owner->SetAffordanceLevel(1.0f);
            owner->SetSpeed(1.5f);
            break;
        case Emotion::Excited:
            owner->SetDesiredAction(Actions::drink);
            owner->SetActionDistance(1.0f);
            owner->SetAffordanceLevel(1.0f);
            owner->SetSpeed(2.0f);
            break;
        default:
            break;
        }
    }

    void PosArousalPosValenceStudent::Exit(Student* owner)
    {
        owner->SetWander(false);
        owner->PutTimerDown();
        owner->SetSpeed(1.0f);
    }

    void NegArousalPosValenceStudent::Enter(Student* owner)
    {
        owner->GetEmotions().UpdateTimer();
        owner->SetWander(true);
        owner->PutTimerDown();
    }

    void NegArousalPosValenceStudent::Execute(Student* owner)
    {
        auto emotion = owner->GetEmotions().GetEmotion();
        if(owner->GetTimer() <= 0)
            owner->SetWander(true);
        
        switch (emotion)
        {
        case Emotion::Content:
            owner->SetDesiredAction(Actions::sit);
            owner->SetActionDistance(1.0f);
            owner->SetAffordanceLevel(1.0f);
            break;
        case Emotion::Relaxed:
            owner->SetDesiredAction(Actions::sit);
            owner->SetActionDistance(1.0f);
            owner->SetAffordanceLevel(1.0f);
            break;
        case Emotion::Calm:
            owner->SetDesiredAction(Actions::none);
            owner->SetActionDistance(1.0f);
            owner->SetAffordanceLevel(0.1f);
            break;
        default:
            break;
        }
    }

    void NegArousalPosValenceStudent::Exit(Student* owner)
    {
        owner->SetWander(false);
    }

    void PosArousalNegValenceStudent::Enter(Student* owner)
    {
        owner->GetEmotions().UpdateTimer();
        owner->SetWander(true);
        owner->SetSpeed(1.5f);
        owner->PutTimerDown();
    }

    void PosArousalNegValenceStudent::Execute(Student* owner)
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

    void PosArousalNegValenceStudent::Exit(Student* owner)
    {
        owner->SetWander(false);
        owner->SetSpeed(1.0f);
    }

    void NegArousalNegValenceStudent::Enter(Student* owner)
    {
        owner->GetEmotions().UpdateTimer();
        owner->SetWander(true);
        owner->SetSpeed(0.75f);
        owner->PutTimerDown();
    }

    void NegArousalNegValenceStudent::Execute(Student* owner)
    {
        auto emotion = owner->GetEmotions().GetEmotion();

        if(owner->GetTimer() <= 0)
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
            owner->SetActionDistance(1.0f);
            owner->SetAffordanceLevel(0.5f);
            owner->SetSpeed(0.75f);
            break;
        case Emotion::Tired:
            owner->SetDesiredAction(Actions::sleep);
            owner->SetActionDistance(1.0f);
            owner->SetAffordanceLevel(0.1f);
            owner->SetSpeed(0.5f);
            break;
        default:
            break;
        }
    }

    void NegArousalNegValenceStudent::Exit(Student* owner)
    {
        owner->SetWander(false);
        owner->SetSpeed(1.0f);
    }
