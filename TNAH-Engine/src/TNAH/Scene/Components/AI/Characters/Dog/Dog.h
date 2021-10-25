#pragma once
#include "TNAH/Scene/Components/AI/Character.h"

namespace tnah {

    class Dog : public Character
    {
    public:
        Dog();
        glm::vec3 OnUpdate(Timestep deltaTime, TransformComponent& transform) override;
        //GetEmotionComponent
        ~Dog() override
        {

        }
        bool spin = false;
        bool canOutput = true;
        EmotionComponent GetEmotions() { return emotions; }
        bool CheckAction(float affordanceValue, float distance, std::string tag) override;
        Emotion mCharacterState;
        glm::vec4 mColour;
        void SetAffordanceLevel(float a) { currentAffordanceLevel = a; }
        void SetActionDistance(float d) { actionDistance = d; }
        std::shared_ptr<StateMachine<Dog>> GetFsm() { return mFsm; }
        void ApplyPlayerAction(PlayerActions givenAction) override;
    private:
        glm::vec3 targetPos;
        std::shared_ptr<StateMachine<Dog>> mFsm;
        float currentAffordanceLevel;
        float BalanceRange(float min, float max, float balanceValue);
        float actionDistance;
        EmotionComponent emotions;
    };
}