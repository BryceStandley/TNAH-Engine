#pragma once
#include "TNAH/Scene/Components/AI/Character.h"

namespace tnah 
{
    /**
     * @class  Dog
     *
     * @brief A class that represents the Dog character in-game. Inherits from the character class
     *
     * @author Dylan Blereau
     * @date   2/11/2021
     */
    class Dog : public Character
    {
    public:

        /**
         * @fn  Dog
         * 
         * @brief  Default constructor
         * 
         * @author Dylan Blereau
         * @date   2/11/2021
         * 
         */
        Dog();

        /**
        * @fn  OnUpdate
        *
        * @brief Updates the character according to deltaTime
        *
        * @author Dylan Blereau
        * @date   2/11/2021
        *
        * @param deltaTime - the timestep of the update
        * @param transform - the transform component of the character
        * @return glm::vec3 - the target position of the character
        */
        glm::vec3 OnUpdate(Timestep deltaTime, TransformComponent& transform) override;

        /**
         * @fn  ~Dog
         *
         * @brief  Destructor
         *
         * @author Dylan Blereau
         * @date   2/11/2021
         *
         */
        ~Dog() override
        {

        }

        /**
         * @fn  GetSpin
         *
         * @brief  Gets and returns the spin flag
         *
         * @author Dylan Blereau
         * @date   2/11/2021
         *
         * @return bool - the spin flag
         */
        bool GetSpin() const { return spin; }

        /**
         * @fn  SetSpin
         *
         * @brief  Sets the spin flag to the value given as a parameter
         *
         * @author Dylan Blereau
         * @date   2/11/2021
         *
         * @param s - value that spin will be set to
         */
        void SetSpin(bool s) { spin = s; }


        /**
         * @fn  GetCanOutput
         *
         * @brief  Gets and returns the current state of the canOutput boolean flag
         *
         * @author Dylan Blereau
         * @date   2/11/2021
         *
         * @return bool - the canOutput boolean
         */
        bool GetCanOutput() const { return canOutput; }

        /**
         * @fn  SetCanOutput
         *
         * @brief  Sets the canOutput boolean flag to the value given as a parameter
         *
         * @author Dylan Blereau
         * @date   2/11/2021
         *
         * @param s - the bool value that canOutput will be set to
         */
        void SetCanOutput(bool s) { canOutput = s; }

        /**
         * @fn  GetEmotions
         *
         * @brief  Returns the EmotionComponent of the Dog
         *
         * @author Dylan Blereau
         * @date   2/11/2021
         *
         * @return The Emotion component of the NPC
         */
        EmotionComponent GetEmotions() { return emotions; }

        /**
         * @fn  CheckAction
         *
         * @brief Checks the action
         *
         * @author Chris Logan
         * @date   2/11/2021
         *
         * @param affordanceValue
         * @param distance
         * @param tag
         * @return boolean pair
         */
        std::pair<bool, bool> CheckAction(float affordanceValue, float distance, std::string tag) override;

        /**
         * @fn  SetAffordanceLevel
         *
         * @brief  Sets the affordance level of the Dog. The affordance level will determine the actions the dog will perform
         *
         * @author Dylan Blereau
         * @date   2/11/2021
         *
         * @param a - the affordance level to be set
         */
        void SetAffordanceLevel(float a) { currentAffordanceLevel = a; }

        /**
         * @fn  SetActionDistance
         *
         * @brief  Sets the action distance of the dog, which is the distance in which it will seek actions
         *
         * @author Dylan Blereau
         * @date   2/11/2021
         *
         * @param d - the action distance to be set
         */
        void SetActionDistance(float d) { actionDistance = d; }

        /**
         * @fn  GetFsm
         *
         * @brief  Gets a pointer to the finite state machine of the dog
         *
         * @author Dylan Blereau
         * @date   2/11/2021
         *
         * @return A pointer to the FSM
         */
        std::shared_ptr<StateMachine<Dog>> GetFsm() { return mFsm; }

        /**
         * @fn  ApplyPlayerAction
         *
         * @brief  Can be used to apply actions of the player to the NPC
         *
         * @author Dylan Blereau
         * @date   2/11/2021
         *
         * @param givenAction - refers to the given player action, which will be applied to the NPC character
         */
        void ApplyPlayerAction(PlayerActions givenAction) override;

        /**
         * @fn  CharacterString
         *
         * @brief Gets the character information string that include Emotion and Action Information
         *
         * @author Dylan Blereau
         * @date   2/11/2021
         *
         * @return string - the Character information string
         */
        std::string CharacterString() override;

        /**
         * @fn  ShootHiss
         *
         * @brief  Starts the hiss dog audio
         *
         * @author Chris Logan
         * @date   2/11/2021
         *
         */
        void ShootHiss();

        /**
         * @fn  StopHiss
         *
         * @brief  Stops the dog hiss audio
         *
         * @author Chris Logan
         * @date   2/11/2021
         *
         */
        void StopHiss() { hiss.m_Paused = true; }

        /**
         * @fn  Shootbark
         *
         * @brief   Starts the dog bark audio
         *
         * @author Chris Logan
         * @date   2/11/2021
         *
         */
        void Shootbark();

        /**
         * @fn  Stopbark
         *
         * @brief  Stops the dog bark audio
         *
         * @author Chris Logan
         * @date   2/11/2021
         *
         */
        void Stopbark() { bark.m_Paused = true; }

        /**
         * @fn  GetCharacterState
         * 
         * @brief  Gets the character emotion state
         * 
         * @author Dylan Blereau
         * @date   2/11/2021
         * 
         * @return Gets the current assigned Emotion
         */
        Emotion GetCharacterState() const { return mCharacterState; }


        /**
         * @fn  SetCharacterState
         *
         * @brief  Sets the character emotion state
         *
         * @author Dylan Blereau
         * @date   2/11/2021
         *
         * @param e - the emotion that will be set
         */
        void SetCharacterState(Emotion e) { mCharacterState = e; }

        /**
         * @fn  GetColour
         * 
         * @brief  Gets the NPC text Colour
         * 
         * @author Dylan Blereau
         * @date   2/11/2021
         * 
         * @return 
         */
        glm::vec4 GetColour() const { return mColour; }

        /**
         * @fn  SetColour
         * 
         * @brief  Sets the NPC text colour
         * 
         * @author Dylan Blereau
         * @date   2/11/2021
         * 
         */
        void SetColour(glm::vec4 colour) { mColour = colour; }

    private:
      
        /// The targetPosition of the character
        glm::vec3 targetPos;

        /// The emotion of the character
        Emotion mCharacterState;

        /// The colour of the text on the UI
        glm::vec4 mColour;

        /// the FSM of the Dog
        std::shared_ptr<StateMachine<Dog>> mFsm;

        /// current Affordance Level of the Dog
        float currentAffordanceLevel = 0;

        /**
         * @fn  BalanceRange
         * 
         * @brief Used to balance the given value between the given min and max values
         * 
         * @author Chris Logan
         * @date   2/11/2021
         * 
         * @param min - the minimum value
         * @param max - the maximum value
         * @param balanceValue - the value that is balanced
         * @return 
         */
        float BalanceRange(float min, float max, float balanceValue);

        /// the action distance of the Dog
        float actionDistance = 0;

        /// the emotion component of the Dog
        EmotionComponent emotions;

        /// the previous action 
        Actions previousState;

        /// the dog angry bark
        AudioSourceComponent hiss = {{"assets/audio/notsocutebark.mp3"}};

        /// the cute dog bark
        AudioSourceComponent bark = {{"assets/audio/cutebark.mp3"}};
        
        /// flag when hiss audio plays
        bool firsthiss = true;

        /// flag when cute bark audio plays
        bool firstbark = true;

        /// flag for whether or not the dog is spinning
        bool spin = false;

        /// flag for whether or not dog is outputting dialogue to screen
        bool canOutput = true;
    };
}