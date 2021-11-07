#pragma once
#include <TNAH-App.h>

using namespace tnah;

    /**
     * @class  Dog
     *
     * @brief A class that represents the Dog character in-game. Inherits from the character class
     *
     * @author Christopher Logan
     * @date   2/11/2021
     */
    class Dog : public tnah::Character
    {
    public:

        /**
         * @fn  Dog
         * 
         * @brief  Default constructor
         * 
         * @author Christopher Logan
         * @date   2/11/2021
         * 
         */
        Dog();

        /**
        * @fn  OnUpdate
        *
        * @brief Updates the character according to deltaTime
        *
        * @author Christopher Logan
        * @date   2/11/2021
        *
        * @param deltaTime - the timestep of the update
        * @param transform - the transform component of the character
        * @return glm::vec3 - the target position of the character
        */
        glm::vec3 OnUpdate(tnah::Timestep deltaTime, tnah::TransformComponent& transform) override;

        /**
         * @fn  ~Dog
         *
         * @brief  Destructor
         *
         * @author Christopher Logan
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
         * @author Christopher Logan
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
         * @author Christopher Logan
         * @date   2/11/2021
         *
         * @param s - value that spin will be set to
         */
        void SetSpin(bool s) { spin = s; }

        /**
         * @fn  GetEmotions
         *
         * @brief  Returns the EmotionComponent of the Dog
         *
         * @author Christopher Logan
         * @date   2/11/2021
         *
         * @return The Emotion component of the NPC
         */
        tnah::EmotionComponent GetEmotions() { return emotions; }

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
         * @author Christopher Logan
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
         * @author Christopher Logan
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
         * @author Christopher Logan
         * @date   2/11/2021
         *
         * @return A pointer to the FSM
         */
        std::shared_ptr<tnah::StateMachine<Dog>> GetFsm() { return mFsm; }

        /**
         * @fn  ApplyPlayerAction
         *
         * @brief  Can be used to apply actions of the player to the NPC
         *
         * @author Christopher Logan
         * @date   2/11/2021
         *
         * @param givenAction - refers to the given player action, which will be applied to the NPC character
         */
        void ApplyPlayerAction(tnah::PlayerActions givenAction) override;

        /**
         * @fn  CharacterString
         *
         * @brief Gets the character information string that include Emotion and Action Information
         *
         * @author Christopher Logan
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
         * @author Christopher Logan
         * @date   2/11/2021
         * 
         * @return Gets the current assigned Emotion
         */
        tnah::Emotion GetCharacterState() const { return mCharacterState; }


        /**
         * @fn  SetCharacterState
         *
         * @brief  Sets the character emotion state
         *
         * @author Christopher Logan
         * @date   2/11/2021
         *
         * @param e - the emotion that will be set
         */
        void SetCharacterState(tnah::Emotion e) { mCharacterState = e; }

        /**
         * @fn  GetColour
         * 
         * @brief  Gets the NPC text Colour
         * 
         * @author Christopher Logan
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
         * @author Christopher Logan
         * @date   2/11/2021
         * 
         */
        void SetColour(glm::vec4 colour) { mColour = colour; }


         void ResetTimer() {timer = 10.0f;};
         void PutTimerDown() {timer = 0.0f;}
    private:
      
        /// The targetPosition of the character
        glm::vec3 targetPos;

        /// The emotion of the character
        tnah::Emotion mCharacterState;

        /// The colour of the text on the UI
        glm::vec4 mColour;

        /// the FSM of the Dog
        std::shared_ptr<tnah::StateMachine<Dog>> mFsm;

        /// current Affordance Level of the Dog
        float currentAffordanceLevel = 0;

        /// the action distance of the Dog
        float actionDistance = 0;

        /// the emotion component of the Dog
        tnah::EmotionComponent emotions;

        /// the previous action 
        tnah::Actions previousState;

        /// the dog angry bark
        tnah::AudioSourceComponent hiss = {{"assets/audio/notsocutebark.mp3"}};

        /// the cute dog bark
        tnah::AudioSourceComponent bark = {{"assets/audio/cutebark.mp3"}};
        
        /// flag when hiss audio plays
        bool firsthiss = true;

        /// flag when cute bark audio plays
        bool firstbark = true;

        /// flag for whether or not the dog is spinning
        bool spin = false;

        /// Internal timer for dialog
        float timer = 10.0f;
    };