#pragma once

#include "../state_machine_switch_base.h"

namespace avp_cruising
{
class AvpCruisingSwitch : public StateMachineSwtichBase
{
public:
    AvpCruisingSwitch() : StateMachineSwtichBase()
    {

    }
public:
    virtual void Init() override {}; 
    virtual void UpdateState() override {};
};
};
