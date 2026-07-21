#pragma once

#include "avp_cruising_event.h"
#include "../../base/state_machine_inputer_base.h"

#include <memory>

namespace parking
{
class AvpCruisingInputer : public StateMachineInputerBase
{
public:
    AvpCruisingInputer() : StateMachineInputerBase(std::make_shared<AvpCruisingEvent>())
    {

    }
public:
    virtual void InitReaders() override 
    {
        std::cout << "Init AvpCruisingInputer Readers" << std::endl;
    };
    virtual void UpdateEvent() override 
    {
        std::cout << "Update AvpCruisingInputer Event" << std::endl;
    };
};
};
