#pragma once
#include "TNAH/Scene/Components/AI/Character.h"
#include "TNAH/Core/Singleton.h"

namespace tnah
{
    //Student States
    class GlobalStudent : public State<Student>
    {
    public:
        virtual void Enter(Student* owner) override;
        virtual void Execute(Student* owner) override;
        virtual void Exit(Student* owner) override;
    };

    class HappyStudent : public State<Student>
    {
    public:
        virtual void Enter(Student* owner) override;
        virtual void Execute(Student* owner) override;
        virtual void Exit(Student* owner) override;
    };

    class ChillStudent : public State<Student>
    {
    public:
        virtual void Enter(Student* owner) override;
        virtual void Execute(Student* owner) override;
        virtual void Exit(Student* owner) override;
    };

    class SadStudent : public State<Student>
    {
    public:
        virtual void Enter(Student* owner) override;
        virtual void Execute(Student* owner) override;
        virtual void Exit(Student* owner) override;
    };

    class PissedOffStudent : public State<Student>
    {
    public:
        virtual void Enter(Student* owner) override;
        virtual void Execute(Student* owner) override;
        virtual void Exit(Student* owner) override;
    };

    typedef  singleton<SadStudent> SadStateStudent;
    typedef  singleton<ChillStudent> ChillStateStudent;
    typedef  singleton<PissedOffStudent> PissedOffStateStudent;
    typedef  singleton<HappyStudent> HappyStateStudent;
    typedef  singleton<GlobalStudent> GlobalStateStudent;
}