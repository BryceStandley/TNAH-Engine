#pragma once
#include "Actions.h"
#include "EmotionComponent.h"
#include "StateMachine.h"
#include "TNAH/Core/TNAHEnableFromThis.h"

namespace tnah
{
    enum CharacterNames
    {
        Player, Rubbish
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
        void LogAction(std::string text, glm::vec4 colour);
        std::string name;
        bool GetWander() {return wander;}
        void SetWander(bool w) {wander = w;}
        void SetSpeed(float s) {speed = s;}
        float GetSpeed() {return speed;}
    private:
        float mDt;
        Actions mDesiredAction;
        float affordanceDistance;
        bool wander = false;
        float speed = 1.0f;
    };

    class Bin : public Character
    {
    public:
        Bin();
        glm::vec3 OnUpdate(Timestep deltaTime) override;
        //GetEmotionComponent
        ~Bin() override
        {

        }
        bool canOutput = true;
        EmotionComponent GetEmotions() {return emotions;}
        void CheckAction(float affordanceValue, float distance) override;
        Emotion mCharacterState;
        glm::vec4 mColour;
        void SetAffordanceLevel(float a) {currentAffordanceLevel = a;}
        void SetActionDistance(float d) {actionDistance = d;}
        std::shared_ptr<StateMachine<Bin>> GetFsm() {return mFsm;}
    private:
        glm::vec3 targetPos;
        std::shared_ptr<StateMachine<Bin>> mFsm;
        float currentAffordanceLevel;
        float BalanceRange(float min, float max, float balanceValue);
        float actionDistance;
        EmotionComponent emotions;
        //Emotion Component
    };

    class PlayerCharacter : public Character
    {
    public:
        PlayerCharacter();
        glm::vec3 OnUpdate(Timestep deltaTime) override;
        //GetEmotionComponent
        
        ~PlayerCharacter() override
        {

        }
        
        bool canOutput = true;
        void CheckAction(float affordanceValue, float distance) override;
        Emotion mCharacterState;
        glm::vec4 mColour;
        void SetAffordanceLevel(float a) {currentAffordanceLevel = a;}
        void SetActionDistance(float d) {actionDistance = d;}
        std::shared_ptr<StateMachine<PlayerCharacter>> GetFsm() {return mFsm;}
    private:
        glm::vec3 targetPos;
        std::shared_ptr<StateMachine<PlayerCharacter>> mFsm;
        float currentAffordanceLevel;
        float BalanceRange(float min, float max, float balanceValue);
        float actionDistance;
    };

    struct CharacterComponent
    {
        CharacterComponent() = default;
        CharacterComponent(CharacterNames characterType)
        {
            switch (characterType)
            {
                case Player:
                    aiCharacter.reset(new PlayerCharacter());
                    break;
                case Rubbish:
                default:
                    aiCharacter.reset(new Bin());
                    break;
            }
        }
        
        std::shared_ptr<Character> aiCharacter;
    };
}
