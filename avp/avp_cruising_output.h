#pragma once

#include "avp_cruising_action.h"
#include "../state_machine_output_base.h"

#include <memory>

namespace avp_cruising
{
class AvpCruisingOutput : public StateMachineOutputBase
{
public:
    AvpCruisingOutput() : StateMachineOutputBase(std::make_shared<AvpCruisingAction>())
    {

    }
public:
    virtual void InitWriters() override {};
    virtual void UpdateAction() override {};
};
};
