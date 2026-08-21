#pragma once

#include "avp_cruising_event.h"
#include "../../../state_machine_inputer_base.h"

#include <iostream>

namespace parking
{
class AvpCruisingInputer : public StateMachineInputerBase<AvpCruisingParam>
{
public:
    AvpCruisingInputer() : StateMachineInputerBase<AvpCruisingParam>(std::make_shared<AvpCruisingEvent>())
    {

    }
public:
    virtual void InitReaders() override 
    {
        std::cout << "Init AvpCruisingInputer Readers" << std::endl;
    };
    void UpdateEvent(std::shared_ptr<AvpCruisingParam> param) override {};
};
};
