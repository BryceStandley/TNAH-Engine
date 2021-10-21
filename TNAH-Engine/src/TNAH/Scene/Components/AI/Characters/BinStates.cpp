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
                break;
            case Emotion::Angry:
                owner->LogAction("Feeling Angry", owner->mColour);
                break;
            case Emotion::Bored:
                owner->LogAction("Feeling Bored", owner->mColour);
                break;
            case Emotion::Calm:
                owner->LogAction("Feeling Calm", owner->mColour);
                break;
            case Emotion::Content:
                owner->LogAction("Feeling Content", owner->mColour);
                break;
            case Emotion::Delighted:
                owner->LogAction("Feeling Delighted", owner->mColour);
                break;
            case Emotion::Depressed:
                owner->LogAction("Feeling Depressed", owner->mColour);
                break;
            case Emotion::Excited:
                owner->LogAction("Feeling Exited", owner->mColour);
                break;
            case Emotion::Frustrated:
                owner->LogAction("Feeling Frustrated", owner->mColour);
                break;
            case Emotion::Happy:
                owner->LogAction("Feeling Happy", owner->mColour);
                break;
            case Emotion::Relaxed:
                owner->LogAction("Feeling Relaxed", owner->mColour);
                break;
            case Emotion::Tired:
                owner->LogAction("Feeling tired", owner->mColour);
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
}