﻿
#pragma once
#include <TNAH-App.h>

using namespace tnah;

 /**
 * @class  Bin
 * 
 * @brief  A class that represents the Bin character in-game. Inherits from the character class
 * 
 * @author Dylan Blereau
 * @date   2/11/2021
 */
    class Bin : public tnah::Character
    {
    public:

        /**
         * @fn  Bin
         * 
         * @brief  Default Constructor
         * 
         * @author Dylan Blereau
         * @date   2/11/2021
         * 
         */
        Bin();

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
        glm::vec3 OnUpdate(Timestep deltaTime,TransformComponent &transform) override;
        
        /**
         * @fn  ~Bin
         * 
         * @brief  Destructor
         * 
         * @author Dylan Blereau
         * @date   2/11/2021
         * 
         */
        ~Bin() override
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
         * @fn  GetEmotions
         *
         * @brief  Returns the EmotionComponent of the Bin
         *
         * @author Dylan Blereau
         * @date   2/11/2021
         *
         * @return The Emotion component of the NPC
         */
        EmotionComponent GetEmotions() {return emotions;}

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
        * @brief  Sets the affordance level of the Bin. The affordance level will determine the actions the bin will perform
        *
        * @author Dylan Blereau
        * @date   2/11/2021
        *
        * @param a - the value affordance level is assigned
        */
        void SetAffordanceLevel(float a) { currentAffordanceLevel = a; }

        /**
         * @fn  SetActionDistance
         *
         * @brief  Sets the action distance of the bin, which is the distance in which it will seek actions
         *
         * @author Dylan Blereau
         * @date   2/11/2021
         *
         * @param d - action distance 
         */
        void SetActionDistance(float d) { actionDistance = d; }

        /**
         * @fn  GetFsm
         *
         * @brief  Gets a pointer to the finite state machine of the bin
         *
         * @author Dylan Blereau
         * @date   2/11/2021
         *
         * @return A pointer to the bin FSM
         */
        std::shared_ptr<StateMachine<Bin>> GetFsm() { return mFsm; }

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
        * @fn  GetCharacterState
        *
        * @brief  Gets the character emotion state
        *
        * @author Dylan Blereau
        * @date   2/11/2021
        *
        * @return The current Emotion of the character
        */
        Emotion GetCharacterState() const { return mCharacterState; }

        /**
         * @fn  SetCharacterState
         * 
         * @brief  Sets the character state to given emotion
         * 
         * @author Dylan Blereau
         * @date   2/11/2021
         * 
         * @param e - the emotion to set 
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
         * @return a vec4 with the colour values
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
     void ResetTimer() {timer = 10.0f;};
     void PutTimerDown() {timer = 0.0f;}
    private:
     float timer = 10.0f;
        /// The targetPosition of the character
        glm::vec3 targetPos;

        /// The emotion of the character
        Emotion mCharacterState;

        /// The colour of the text on the UI
        glm::vec4 mColour;

        /// the FSM of the Bin
        std::shared_ptr<StateMachine<Bin>> mFsm;

        /// current Affordance Level of the Bin
        float currentAffordanceLevel = 0;

        /// the action distance of the Bin
        float actionDistance = 0;

        /// flag for whether or not the Bin is spinning
        bool spin = false;

        /// the emotion component of the Bin
        EmotionComponent emotions;

        /// the previous action 
        Actions previousState;
    };