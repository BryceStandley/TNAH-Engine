#pragma once
#include "TNAH/Scene/Components/AI/Character.h"
#include "TNAH/Core/Singleton.h"

namespace tnah
{
    class GlobalBin : public State<Bin>
    {
    public:
        virtual void Enter(Bin* owner) override;
        virtual void Execute(Bin* owner) override;
        virtual void Exit(Bin* owner) override;
    };
    
    typedef  singleton<GlobalBin> global_bin;
}