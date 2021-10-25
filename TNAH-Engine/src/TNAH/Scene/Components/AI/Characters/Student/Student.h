#pragma once
#include "TNAH/Scene/Components/AI/Character.h"

namespace tnah {
    class Student : public Character
    {
    public:
        Student();
        glm::vec3 OnUpdate(Timestep deltaTime, TransformComponent& transform) override;
        //GetEmotionComponent
        ~Student() override
        {

        }

        bool canOutput = true;
        EmotionComponent GetEmotions() { return emotions; }
        std::pair<bool, bool> CheckAction(float affordanceValue, float distance, std::string tag) override;
        Emotion mCharacterState;
        glm::vec4 mColour;
        void SetAffordanceLevel(float a) { currentAffordanceLevel = a; }
        void SetActionDistance(float d) { actionDistance = d; }
        std::shared_ptr<StateMachine<Student>> GetFsm() { return mFsm; }
        void ApplyPlayerAction(PlayerActions givenAction) override;
        std::string CharacterString() override;
        Actions previousState;
    private:
        glm::vec3 targetPos;
        std::shared_ptr<StateMachine<Student>> mFsm;
        float currentAffordanceLevel;
        float BalanceRange(float min, float max, float balanceValue);
        float actionDistance;
        EmotionComponent emotions;
    };
}