#pragma once

#include "avp_cruising_event.h"
#include "../state_machine_input_base.h"

#include <memory>

namespace avp_cruising
{
class AvpCruisingInput : public StateMachineInputBase
{
public:
    AvpCruisingInput() : StateMachineInputBase(std::make_shared<AvpCruisingEvent>())
    {

    }
public:
    virtual void InitReaders() override {};
    virtual void UpdateEvent() override {};
};
};
