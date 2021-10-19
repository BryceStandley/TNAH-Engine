#pragma once
#include "Actions.h"
#include "StateMachine.h"
#include "TNAH/Core/TNAHEnableFromThis.h"

namespace tnah
{
    enum CharacterNames
    {
        BinName, Sweeper, Coffee
    };
    
    class Character
    {
    public:
        virtual glm::vec3 OnUpdate(Timestep deltaTime) = 0;
        virtual ~Character() = default;
        float GetDeltaTime() const {return mDt;}
        void SetDeltaTime(const float t) {mDt = t;}
        void SetDesiredAction(const Actions a) {mDesiredAction = a;}
        Actions GetDesiredAction() const {return mDesiredAction;}
        void SetDistance(const float d) {affordanceDistance = d;}
        float GetDistance() const {return affordanceDistance;}
        virtual void CheckAction(float affordanceValue, float distance) = 0;
    private:
        float mDt;
        Actions mDesiredAction;
        float affordanceDistance;
    };

    class Bin : public Character
    {
    public:
        Bin();
        glm::vec3 OnUpdate(Timestep deltaTime) override;
        //GetEmotionComponent
        ~Bin() override
        {
            SetDesiredAction(kick);
            SetDistance(10);
        }

        void CheckAction(float affordanceValue, float distance) override;
    private:
        glm::vec3 targetPos;
        std::shared_ptr<StateMachine<Bin>> mFsm;
        float currentAffordanceLevel;
        float BalanceRange(float min, float max, float balanceValue);
        float actionDistance;
        //Emotion Component
    };

    struct CharacterComponent
    {
        CharacterComponent()
        {
            aiCharacter.reset(new Bin());
        }
        
        std::shared_ptr<Character> aiCharacter;
    };
}
