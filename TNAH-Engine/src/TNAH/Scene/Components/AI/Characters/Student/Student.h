#pragma once
#include "TNAH/Scene/Components/AI/Character.h"

namespace tnah {

    /**
     * @class  Student
     *
     * @brief A class that represents the Student character in-game. Inherits from the character class
     *
     * @author Dylan Blereau
     * @date   2/11/2021
     */
    class Student : public Character
    {
    public:

        /**
         * @fn  Student
         * 
         * @brief  Default Constructor
         * 
         * @author Dylan Blereau
         * @date   2/11/2021
         * 
         */
        Student();

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
         * @fn  ~Student
         *
         * @brief  Destructor
         *
         * @author Dylan Blereau
         * @date   2/11/2021
         *
         */
        ~Student() override
        {

        }

        /**
         * @fn  GetEmotions
         *
         * @brief  Returns the EmotionComponent of the Student
         *
         * @author Dylan Blereau
         * @date   2/11/2021
         *
         * @return The Emotion Component
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
         * @brief  Sets the affordance level of the Student. The affordance level will determine the actions the student will perform
         *
         * @author Dylan Blereau
         * @date   2/11/2021
         *
         * @param a - the value that will be set
         */
        void SetAffordanceLevel(float a) { currentAffordanceLevel = a; }

        /**
         * @fn  SetActionDistance
         *
         * @brief  Sets the action distance of the student, which is the distance in which it will seek actions
         *
         * @author Dylan Blereau
         * @date   2/11/2021
         *
         * @param d - the value that will be set
         */
        void SetActionDistance(float d) { actionDistance = d; }

        /**
         * @fn  GetFsm
         *
         * @brief  Gets a pointer to the finite state machine of the student
         *
         * @author Dylan Blereau
         * @date   2/11/2021
         *
         * @return pointer to student fsm
         */
        std::shared_ptr<StateMachine<Student>> GetFsm() { return mFsm; }

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
         * @return Emotion the character currently has
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
         * @return vec4 representing the colour
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
     void ResetTimer() {timer = 10.0f;}
     void PutTimerDown() {timer = 0.0f;}
    float GetTimer() const {return timer;}
    private:
     float timer = 10.0f;
        /// The targetPosition of the character
        glm::vec3 targetPos;

        /// The emotion of the character
        Emotion mCharacterState;

        /// The colour of the text on the UI
        glm::vec4 mColour;

        /// the FSM of the Student
        std::shared_ptr<StateMachine<Student>> mFsm;

        /// current Affordance Level of the Student
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
         * @return float
         */
        float BalanceRange(float min, float max, float balanceValue);

        /// the action distance of the Student
        float actionDistance = 0;

        /// the emotion component of the Student
        EmotionComponent emotions;

        /// the previous action 
        Actions previousState;
    };
}