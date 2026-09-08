#pragma once

#include "avp_mapping_event.h"
#include "avp_mapping_param.h"
#include "../../../state_machine_inputer_base.h"

#include <iostream>

namespace parking
{
class AvpMappingInputer : public StateMachineInputer
{
public:
    virtual void InitReaders() override 
    {
        std::cout << "Init AvpMappingInputer Readers" << std::endl;
    };
    virtual void UpdateEvent() override {};
};
};
