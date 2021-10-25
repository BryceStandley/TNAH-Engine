#pragma once

#include "TNAH/Scene/Components/AI/Characters/Bin/Bin.h"
namespace tnah {
    enum CharacterNames
    {
        Rubbish, StudentAi, BirdAi
    };


    struct CharacterComponent
    {
        CharacterComponent()
        {
            aiCharacter.reset(new Bin()); 
        }

        CharacterComponent(CharacterNames characterType)
        {
            SetCharacter(characterType);
        }

        void SetCharacter(CharacterNames characterType)
        {
            switch (characterType)
            {
                /*case StudentAi:
                aiCharacter.reset(new Student());
                break;
                case BirdAi:
                aiCharacter.reset((new Bird()));
                break;*/
                case Rubbish:
            default:
                aiCharacter.reset(new Bin());
                break;
            }
        }

        std::shared_ptr<Character> aiCharacter;
    };
}