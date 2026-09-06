#pragma once

#include "avp_mapping_event.h"
#include "avp_mapping_param.h"
#include "../../../state_machine_inputer_base.h"

#include <iostream>

namespace parking
{
class AvpMappingInputer : public StateMachineInputerBase
{
public:
    AvpMappingInputer() : StateMachineInputerBase(std::make_shared<AvpMappingEvent>())
    {

    }
public:
    virtual void InitReaders() override 
    {
        std::cout << "Init AvpMappingInputer Readers" << std::endl;
    };
    void UpdateEvent() override {};
};
};
