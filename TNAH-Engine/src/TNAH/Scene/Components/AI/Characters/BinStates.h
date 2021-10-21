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

    class TiredBin : public State<Bin>
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

    class SadBin : public State<Bin>
    {
    public:
        virtual void Enter(Bin* owner) override;
        virtual void Execute(Bin* owner) override;
        virtual void Exit(Bin* owner) override;
    };

    class DelightedBin : public State<Bin>
    {
    public:
        virtual void Enter(Bin* owner) override;
        virtual void Execute(Bin* owner) override;
        virtual void Exit(Bin* owner) override;
    };

    class CalmBin : public State<Bin>
    {
    public:
        virtual void Enter(Bin* owner) override;
        virtual void Execute(Bin* owner) override;
        virtual void Exit(Bin* owner) override;
    };

    class AngryBin : public State<Bin>
    {
    public:
        virtual void Enter(Bin* owner) override;
        virtual void Execute(Bin* owner) override;
        virtual void Exit(Bin* owner) override;
    };

    class TenseBin : public State<Bin>
    {
    public:
        virtual void Enter(Bin* owner) override;
        virtual void Execute(Bin* owner) override;
        virtual void Exit(Bin* owner) override;
    };

    class BoredBin : public State<Bin>
    {
    public:
        virtual void Enter(Bin* owner) override;
        virtual void Execute(Bin* owner) override;
        virtual void Exit(Bin* owner) override;
    };

    class ContentBin : public State<Bin>
    {
    public:
        virtual void Enter(Bin* owner) override;
        virtual void Execute(Bin* owner) override;
        virtual void Exit(Bin* owner) override;
    };

    class DepressedBin : public State<Bin>
    {
    public:
        virtual void Enter(Bin* owner) override;
        virtual void Execute(Bin* owner) override;
        virtual void Exit(Bin* owner) override;
    };

    class ExcitedBin : public State<Bin>
    {
    public:
        virtual void Enter(Bin* owner) override;
        virtual void Execute(Bin* owner) override;
        virtual void Exit(Bin* owner) override;
    };

    class FrustratedBin : public State<Bin>
    {
    public:
        virtual void Enter(Bin* owner) override;
        virtual void Execute(Bin* owner) override;
        virtual void Exit(Bin* owner) override;
    };
    
    
    typedef  singleton<GlobalBin> global_bin;
    typedef  singleton<TiredBin> Tired_bin;
    typedef  singleton<AngryBin> Angry_bin;
    typedef  singleton<HappyBin> Happy_bin;
    typedef  singleton<SadBin> Sad_bin;
    typedef  singleton<DepressedBin> Depressed_bin;
    typedef  singleton<FrustratedBin> Frustrated_bin;
    typedef  singleton<ExcitedBin> Excited_bin;
    typedef  singleton<ContentBin> Content_bin;
    typedef  singleton<BoredBin> Bored_bin;
    typedef  singleton<TenseBin> Tense_bin;
    typedef  singleton<CalmBin> Calm_bin;
    typedef  singleton<DelightedBin> Delighted_bin;
}