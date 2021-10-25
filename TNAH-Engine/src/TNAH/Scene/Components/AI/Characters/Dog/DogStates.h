#pragma once
#include "Dog.h"
#include "TNAH/Scene/Components/AI/StateMachine.h"
#include "TNAH/Core/Singleton.h"

namespace tnah
{
    //Bird States
    class GlobalDog : public State<Dog>
    {
    public:
        virtual void Enter(Dog* owner) override;
        virtual void Execute(Dog* owner) override;
        virtual void Exit(Dog* owner) override;
    };

    class HappyDog : public State<Dog>
    {
    public:
        virtual void Enter(Dog* owner) override;
        virtual void Execute(Dog* owner) override;
        virtual void Exit(Dog* owner) override;
    };

    class ChillDog : public State<Dog>
    {
    public:
        virtual void Enter(Dog* owner) override;
        virtual void Execute(Dog* owner) override;
        virtual void Exit(Dog* owner) override;
    };

    class SadDog : public State<Dog>
    {
    public:
        virtual void Enter(Dog* owner) override;
        virtual void Execute(Dog* owner) override;
        virtual void Exit(Dog* owner) override;
    };

    class PissedOffDog : public State<Dog>
    {
    public:
        virtual void Enter(Dog* owner) override;
        virtual void Execute(Dog* owner) override;
        virtual void Exit(Dog* owner) override;
    };

    typedef  singleton<SadDog> SadStateDog;
    typedef  singleton<ChillDog> ChillStateDog;
    typedef  singleton<PissedOffDog> PissedOffStateDog;
    typedef  singleton<HappyDog> HappyStateDog;
    typedef  singleton<GlobalDog> GlobalStateDog;
}

