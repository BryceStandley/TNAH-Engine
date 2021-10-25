#pragma once
#include "Actions.h"
#include "EmotionComponent.h"
#include "StateMachine.h"
#include "TNAH/Core/TNAHEnableFromThis.h"

namespace tnah
{
    class Character
    {
    public:
        virtual glm::vec3 OnUpdate(Timestep deltaTime,TransformComponent &transform) = 0;
        virtual ~Character() = default;
        float GetDeltaTime() const {return mDt;}
        void SetDeltaTime(const float t) {mDt = t;}
        void SetDesiredAction(const Actions a) {mDesiredAction = a;}
        Actions GetDesiredAction() const {return mDesiredAction;}
        void SetDistance(const float d) {affordanceDistance = d;}
        float GetDistance() const {return affordanceDistance;}
        virtual std::pair<bool, bool> CheckAction(float affordanceValue, float distance, std::string tag) = 0;
        void LogAction(std::string text, glm::vec4 colour);
        std::string name;
        bool GetWander() {return wander;}
        void SetWander(bool w) {wander = w;}
        void SetSpeed(float s) {speed = s;}
        float GetSpeed() {return speed;}
        virtual void ApplyPlayerAction(PlayerActions givenAction) = 0;
        virtual std::string CharacterString() = 0;
        std::string GetActionString(Actions action);
    private:
        float mDt;
        Actions mDesiredAction;
        float affordanceDistance;
        bool wander = false;
        float speed = 1.0f;
    };
   
}
