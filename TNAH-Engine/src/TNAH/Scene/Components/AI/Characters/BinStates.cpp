#include "tnahpch.h"
#include "BinStates.h"

namespace tnah
{
    //Bin global
    void GlobalBin::Enter(Bin* owner)
    {
        //TNAH_CORE_INFO("Enter called");
    }

    void GlobalBin::Execute(Bin*owner)
    {
        auto emotion = owner->GetEmotions().GetEmotion();
        if(owner->mCharacterState != emotion)
        {
            switch (emotion)
            {
            case Emotion::Tense:
                owner->LogAction("Feeling Tense", owner->mColour);
                if(owner->mCharacterState != Emotion::Angry || owner-> mCharacterState != Emotion::Frustrated)
                    owner->GetFsm()->changeState(&PissedOffStateBin::getInstance());
                break;
            case Emotion::Angry:
                owner->LogAction("Feeling Angry", owner->mColour);
                if(owner->mCharacterState != Emotion::Tense || owner-> mCharacterState != Emotion::Frustrated)
                    owner->GetFsm()->changeState(&PissedOffStateBin::getInstance());
                break;
            case Emotion::Frustrated:
                owner->LogAction("Feeling Frustrated", owner->mColour);
                if(owner->mCharacterState != Emotion::Tense || owner-> mCharacterState != Emotion::Angry)
                    owner->GetFsm()->changeState(&PissedOffStateBin::getInstance());
                break;
            case Emotion::Calm:
                owner->LogAction("Feeling Calm", owner->mColour);
                if(owner->mCharacterState != Emotion::Relaxed || owner-> mCharacterState != Emotion::Content)
                    owner->GetFsm()->changeState(&ChillStateBin::getInstance());
                break;
            case Emotion::Content:
                owner->LogAction("Feeling Content", owner->mColour);
                if(owner->mCharacterState != Emotion::Calm || owner-> mCharacterState != Emotion::Relaxed)
                    owner->GetFsm()->changeState(&ChillStateBin::getInstance());
                break;
            case Emotion::Relaxed:
                owner->LogAction("Feeling Relaxed", owner->mColour);
                if(owner->mCharacterState != Emotion::Calm || owner-> mCharacterState != Emotion::Content)
                    owner->GetFsm()->changeState(&ChillStateBin::getInstance());
                break;
            case Emotion::Delighted:
                owner->LogAction("Feeling Delighted", owner->mColour);
                if(owner->mCharacterState != Emotion::Happy || owner-> mCharacterState != Emotion::Excited)
                    owner->GetFsm()->changeState(&HappyStateBin::getInstance());
                break;
            case Emotion::Excited:
                owner->LogAction("Feeling Exited", owner->mColour);
                if(owner->mCharacterState != Emotion::Happy || owner-> mCharacterState != Emotion::Delighted)
                    owner->GetFsm()->changeState(&HappyStateBin::getInstance());
                break;
            case Emotion::Happy:
                owner->LogAction("Feeling Happy", owner->mColour);
                if(owner->mCharacterState != Emotion::Excited || owner-> mCharacterState != Emotion::Delighted)
                    owner->GetFsm()->changeState(&HappyStateBin::getInstance());
                break;
            case Emotion::Tired:
                owner->LogAction("Feeling tired", owner->mColour);
                if(owner->mCharacterState != Emotion::Bored || owner-> mCharacterState != Emotion::Depressed)
                    owner->GetFsm()->changeState(&SadStateBin::getInstance());
                break;
            case Emotion::Bored:
                owner->LogAction("Feeling Bored", owner->mColour);
                if(owner->mCharacterState != Emotion::Tired || owner-> mCharacterState != Emotion::Depressed)
                    owner->GetFsm()->changeState(&SadStateBin::getInstance());
                break;
            case Emotion::Depressed:
                owner->LogAction("Feeling Depressed", owner->mColour);
                if(owner->mCharacterState != Emotion::Tired || owner-> mCharacterState != Emotion::Bored)
                    owner->GetFsm()->changeState(&SadStateBin::getInstance());
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
    
    void GlobalBin::Exit(Bin*owner)
    {
            
    }

    void HappyBin::Enter(Bin* owner)
    {
        owner->SetWander(true);
    }

    void HappyBin::Execute(Bin* owner)
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

    void HappyBin::Exit(Bin* owner)
    {
        owner->spin = false;
        owner->SetWander(false);
        owner->canOutput = true;
    }

    void ChillBin::Enter(Bin* owner)
    {

    }

    void ChillBin::Execute(Bin* owner)
    {
        //Heads home to idle
    }

    void ChillBin::Exit(Bin* owner)
    {

    }

    void PissedOffBin::Enter(Bin* owner)
    {
        owner->SetWander(true);
        owner->SetSpeed(1.5f);
        owner->canOutput = true;
    }

    void PissedOffBin::Execute(Bin* owner)
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

    void PissedOffBin::Exit(Bin* owner)
    {
        owner->SetWander(false);
        owner->SetSpeed(1.0f);
        owner->canOutput = true;
    }

    void SadBin::Enter(Bin* owner)
    {
        owner->SetWander(true);
        owner->SetSpeed(0.75f);
    }

    void SadBin::Execute(Bin* owner)
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

    void SadBin::Exit(Bin* owner)
    {
        owner->SetWander(false);
        owner->SetSpeed(1.0f);
        owner->canOutput = true;
    }
}