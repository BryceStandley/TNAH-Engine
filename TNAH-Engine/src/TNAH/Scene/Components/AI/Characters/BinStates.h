#pragma once
#include "TNAH/Scene/Components/AI/Character.h"
#include "TNAH/Core/Singleton.h"

namespace tnah
{
    //Bin States
    class GlobalBin : public State<Bin>
    {
    public:
        virtual void Enter(Bin* owner) override;
        virtual void Execute(Bin* owner) override;
        virtual void Exit(Bin* owner) override;
    };

    class HappyBin : public State<Bin>
    {
    public:
        virtual void Enter(Bin* owner) override;
        virtual void Execute(Bin* owner) override;
        virtual void Exit(Bin* owner) override;
    };

    class ChillBin : public State<Bin>
    {
    public:
        virtual void Enter(Bin* owner) override;
        virtual void Execute(Bin* owner) override;
        virtual void Exit(Bin* owner) override;
    };

    class SadBin : public State<Bin>
    {
    public:
        virtual void Enter(Bin* owner) override;
        virtual void Execute(Bin* owner) override;
        virtual void Exit(Bin* owner) override;
    };

    class PissedOffBin : public State<Bin>
    {
    public:
        virtual void Enter(Bin* owner) override;
        virtual void Execute(Bin* owner) override;
        virtual void Exit(Bin* owner) override;
    };
    
    typedef  singleton<SadBin> SadStateBin;
    typedef  singleton<ChillBin> ChillStateBin;
    typedef  singleton<PissedOffBin> PissedOffStateBin;
    typedef  singleton<HappyBin> HappyStateBin;
    typedef  singleton<GlobalBin> GlobalStateBin;
}