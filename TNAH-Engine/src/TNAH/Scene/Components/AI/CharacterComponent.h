#pragma once

#include "TNAH/Scene/Components/AI/Characters/Rubbish/Bin.h"
#include "TNAH/Scene/Components/AI/Characters/Dog/Dog.h"
#include "TNAH/Scene/Components/AI/Characters/Student/Student.h"

namespace tnah {
    /**
     * @brief enums that represent the three NPC types
     */
    enum CharacterNames
    {
        Rubbish = 1, StudentAi = 2, DogAi = 3
    };

    struct CharacterComponent
    {
        /**
         * @fn  CharacterComponent
         * 
         * @brief default constructor of the character component struct 
         * 
         * @author Dylan Blereau
         * @date   2/11/2021
         * 
         */
        CharacterComponent()
        {
            aiCharacter.reset(new Bin());
            currentCharacter = CharacterNames::Rubbish;
        }

        /**
         * @fn  CharacterComponent
         * 
         * @brief  Constructor for the character component that takes in the character type name and sets the character accordingly
         * 
         * @author Dylan Blereau
         * @date   2/11/2021
         * 
         * @param characterType
         */
        CharacterComponent(CharacterNames characterType)
        {
            SetCharacter(characterType);
        }

        /**
         * @fn  SetCharacter
         * 
         * @brief  Sets the character using the given characterType name
         * 
         * @author Dylan Blereau
         * @date   2/11/2021
         * 
         * @param characterType
         */
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
            currentCharacter = characterType;
        }

        /// A pointer to the an instance of character class
        std::shared_ptr<Character> aiCharacter;
        
        /// character name value of the current character
        CharacterNames currentCharacter;
    };
}