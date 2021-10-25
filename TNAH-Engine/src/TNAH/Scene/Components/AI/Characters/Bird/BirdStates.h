#pragma once
#include "Bird.h"
#include "TNAH/Scene/Components/AI/StateMachine.h"
#include "TNAH/Core/Singleton.h"

namespace tnah
{
    //Bird States
    class GlobalBird : public State<Bird>
    {
    public:
        virtual void Enter(Bird* owner) override;
        virtual void Execute(Bird* owner) override;
        virtual void Exit(Bird* owner) override;
    };

    class HappyBird : public State<Bird>
    {
    public:
        virtual void Enter(Bird* owner) override;
        virtual void Execute(Bird* owner) override;
        virtual void Exit(Bird* owner) override;
    };

    class ChillBird : public State<Bird>
    {
    public:
        virtual void Enter(Bird* owner) override;
        virtual void Execute(Bird* owner) override;
        virtual void Exit(Bird* owner) override;
    };

    class SadBird : public State<Bird>
    {
    public:
        virtual void Enter(Bird* owner) override;
        virtual void Execute(Bird* owner) override;
        virtual void Exit(Bird* owner) override;
    };

    class PissedOffBird : public State<Bird>
    {
    public:
        virtual void Enter(Bird* owner) override;
        virtual void Execute(Bird* owner) override;
        virtual void Exit(Bird* owner) override;
    };

    typedef  singleton<SadBird> SadStateBird;
    typedef  singleton<ChillBird> ChillStateBird;
    typedef  singleton<PissedOffBird> PissedOffStateBird;
    typedef  singleton<HappyBird> HappyStateBird;
    typedef  singleton<GlobalBird> GlobalStateBird;
}

