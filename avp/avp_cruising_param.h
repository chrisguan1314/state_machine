#pragma once

#include "../state_machine_param_base.h"

namespace avp_cruising
{
class AvpCruisingParam : public StateMachineParamBase
{
public:
    AvpCruisingParam() : StateMachineParamBase()
    {

    }
public:
    virtual void Init() override {}; 
    virtual void UpdateParam() override {};
};
};
