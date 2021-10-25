#pragma once

#include "TNAH/Scene/Components/AI/Characters/Rubbish/Bin.h"
#include "TNAH/Scene/Components/AI/Characters/Dog/Dog.h"
#include "TNAH/Scene/Components/AI/Characters/Student/Student.h"

namespace tnah {
    enum CharacterNames
    {
        Rubbish, StudentAi, DogAi
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
                case StudentAi:
                    aiCharacter.reset(new Student());
                    break;
                case DogAi:
                    aiCharacter.reset((new Dog()));
                    break;
                case Rubbish:
                    aiCharacter.reset((new Bin()));
                    break;
            default:
                aiCharacter.reset(new Bin());
                break;
            }
        }

        std::shared_ptr<Character> aiCharacter;
    };
}