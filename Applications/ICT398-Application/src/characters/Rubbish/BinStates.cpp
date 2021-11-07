#include "BinStates.h"

    //Bin global
    void GlobalBin::Enter(Bin* owner)
    {
        //TNAH_CORE_INFO("Enter called");
    }

    void GlobalBin::Execute(Bin*owner)
    {
        auto emotion = owner->GetEmotions().GetEmotion();
        if(owner->GetCharacterState() != emotion)
        {
            switch (emotion)
            {
            case Emotion::Tense:
                owner->LogAction("Feeling Tense", owner->GetColour());
                if(owner->GetCharacterState() != Emotion::Angry && owner-> GetCharacterState() != Emotion::Frustrated)
                    owner->GetFsm()->changeState(&AngryStateBin::getInstance());
                break;
            case Emotion::Angry:
                owner->LogAction("Feeling Angry", owner->GetColour());
                if(owner->GetCharacterState() != Emotion::Tense && owner-> GetCharacterState() != Emotion::Frustrated)
                    owner->GetFsm()->changeState(&AngryStateBin::getInstance());
                break;
            case Emotion::Frustrated:
                owner->LogAction("Feeling Frustrated", owner->GetColour());
                if(owner->GetCharacterState() != Emotion::Tense && owner-> GetCharacterState() != Emotion::Angry)
                    owner->GetFsm()->changeState(&AngryStateBin::getInstance());
                break;
            case Emotion::Calm:
                owner->LogAction("Feeling Calm", owner->GetColour());
                if(owner->GetCharacterState() != Emotion::Relaxed && owner-> GetCharacterState() != Emotion::Content)
                    owner->GetFsm()->changeState(&ChillStateBin::getInstance());
                break;
            case Emotion::Content:
                owner->LogAction("Feeling Content", owner->GetColour());
                if(owner->GetCharacterState() != Emotion::Calm && owner-> GetCharacterState() != Emotion::Relaxed)
                    owner->GetFsm()->changeState(&ChillStateBin::getInstance());
                break;
            case Emotion::Relaxed:
                owner->LogAction("Feeling Relaxed", owner->GetColour());
                if(owner->GetCharacterState() != Emotion::Calm && owner-> GetCharacterState() != Emotion::Content)
                    owner->GetFsm()->changeState(&ChillStateBin::getInstance());
                break;
            case Emotion::Delighted:
                owner->LogAction("Feeling Delighted", owner->GetColour());
                if(owner->GetCharacterState() != Emotion::Happy && owner-> GetCharacterState() != Emotion::Excited)
                    owner->GetFsm()->changeState(&HappyStateBin::getInstance());
                break;
            case Emotion::Excited:
                owner->LogAction("Feeling Exited", owner->GetColour());
                if(owner->GetCharacterState() != Emotion::Happy && owner-> GetCharacterState() != Emotion::Delighted)
                    owner->GetFsm()->changeState(&HappyStateBin::getInstance());
                break;
            case Emotion::Happy:
                owner->LogAction("Feeling Happy", owner->GetColour());
                if(owner->GetCharacterState() != Emotion::Excited && owner-> GetCharacterState() != Emotion::Delighted)
                    owner->GetFsm()->changeState(&HappyStateBin::getInstance());
                break;
            case Emotion::Tired:
                owner->LogAction("Feeling tired", owner->GetColour());
                if(owner->GetCharacterState() != Emotion::Bored && owner-> GetCharacterState() != Emotion::Depressed)
                    owner->GetFsm()->changeState(&SadStateBin::getInstance());
                break;
            case Emotion::Bored:
                owner->LogAction("Feeling Bored", owner->GetColour());
                if(owner->GetCharacterState() != Emotion::Tired && owner-> GetCharacterState() != Emotion::Depressed)
                    owner->GetFsm()->changeState(&SadStateBin::getInstance());
                break;
            case Emotion::Depressed:
                owner->LogAction("Feeling Depressed", owner->GetColour());
                if(owner->GetCharacterState() != Emotion::Tired && owner-> GetCharacterState() != Emotion::Bored)
                    owner->GetFsm()->changeState(&SadStateBin::getInstance());
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
    
    void GlobalBin::Exit(Bin*owner)
    {
            
    }

    void PosArousalPosValenceBin::Enter(Bin* owner)
    {
        owner->GetEmotions().UpdateTimer();
        owner->SetWander(true);
        owner->PutTimerDown();
    }

    void PosArousalPosValenceBin::Execute(Bin* owner)
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
                owner->SetSpin(true);
                break;
            default:
                break;
        }
    }

    void PosArousalPosValenceBin::Exit(Bin* owner)
    {
        owner->SetSpin(false);
        owner->SetWander(false);
    }

    void NegArousalPosValenceBin::Enter(Bin* owner)
    {
        owner->GetEmotions().UpdateTimer();
        owner->SetWander(true);
        owner->PutTimerDown();
    }

    void NegArousalPosValenceBin::Execute(Bin* owner)
    {
        auto emotion = owner->GetEmotions().GetEmotion();

        switch (emotion)
        {
        case Emotion::Content:
            owner->SetDesiredAction(Actions::none);
            owner->SetSpeed(0.75f);
            break;
        case Emotion::Relaxed:
            owner->SetDesiredAction(Actions::none);
            owner->SetSpeed(0.5f);
            break;
        case Emotion::Calm:
            owner->SetDesiredAction(Actions::none);
            owner->SetSpeed(0.1f);
            break;
        default:
            break;
        }
    }

    void NegArousalPosValenceBin::Exit(Bin* owner)
    {
        owner->SetWander(false);
        owner->SetSpeed(1.0f);
    }

    void PosArousalNegValenceBin::Enter(Bin* owner)
    {
        owner->GetEmotions().UpdateTimer();
        owner->SetWander(true);
        owner->SetSpeed(1.5f);
        owner->PutTimerDown();
    }

    void PosArousalNegValenceBin::Execute(Bin* owner)
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

    void PosArousalNegValenceBin::Exit(Bin* owner)
    {
        owner->SetWander(false);
        owner->SetSpeed(1.0f);
    }

    void NegArousalNegValenceBin::Enter(Bin* owner)
    {
        owner->GetEmotions().UpdateTimer();
        owner->SetWander(true);
        owner->SetSpeed(0.75f);
        owner->PutTimerDown();
    }

    void NegArousalNegValenceBin::Execute(Bin* owner)
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

    void NegArousalNegValenceBin::Exit(Bin* owner)
    {
        owner->SetWander(false);
        owner->SetSpeed(1.0f);
    }