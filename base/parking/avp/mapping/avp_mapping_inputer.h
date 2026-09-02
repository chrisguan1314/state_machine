#pragma once

#include "avp_mapping_event.h"
#include "avp_mapping_param.h"
#include "../../../state_machine_inputer_base.h"

#include <iostream>

namespace parking
{
class AvpMappingInputer : public StateMachineInputerBase<AvpMappingParam>
{
public:
    AvpMappingInputer() : StateMachineInputerBase<AvpMappingParam>(std::make_shared<AvpMappingEvent>())
    {

    }
public:
    virtual void InitReaders() override 
    {
        std::cout << "Init AvpMappingInputer Readers" << std::endl;
    };
    void UpdateEvent(std::shared_ptr<AvpMappingParam> param) override {};
};
};
